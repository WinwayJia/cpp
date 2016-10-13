#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdarg.h>
#include <signal.h> 
#include <errno.h>  
#include <fcntl.h>
#include <unistd.h>

#include "simple_config.h"
#include "simple_log.h"

// log context
const int CONST_MAX_SINGLE_LOG_SIZE = 2048;
const int CONST_ONE_DAY_SECONDS = (24 * 60 * 60);

int log_level = DEBUG_LEVEL;
std::string g_dir;
std::string g_config_file;
bool use_file_appender = false;
CFileAppender g_file_appender;

CFileAppender::CFileAppender() {
    m_is_inited = false;
    m_retain_day = -1;
}

CFileAppender::~CFileAppender() {
    if (m_fs.is_open()) {
        m_fs.close();
    }
}

int CFileAppender::init(std::string& dir, const std::string& log_file) {
    if (!dir.empty()) {
        int ret = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (ret != 0 && errno != EEXIST) {
            printf("mkdir error which dir:%s err:%s\n", dir.c_str(), strerror(errno));
            m_is_inited = true;
            return -1;
        }
    } else {
        dir = "."; // current dir
    }
    m_log_dir = dir;
    m_log_file = log_file;
    m_log_file_path = dir + "/" + log_file;
    m_fs.open(m_log_file_path.c_str(), std::fstream::out | std::fstream::app);
    m_is_inited = true;

    return 0;
}

int CFileAppender::write_log(char *log, const char *format, va_list ap) {
    CCriticalSectionHelper lock_help(m_lock);

    if (m_fs.is_open()) {
        vsnprintf(log, CONST_MAX_SINGLE_LOG_SIZE - 1, format, ap);
        m_fs << log << "\n";
        m_fs.flush();
    }

    return 0;
}

int CFileAppender::shift_file_if_need(struct timeval tv, struct timezone tz) {
    if (0 == m_last_sec) {
        m_last_sec = tv.tv_sec;
        return 0;
    }
    long fix_now_sec = tv.tv_sec - tz.tz_minuteswest * 60;
    long fix_last_sec = m_last_sec - tz.tz_minuteswest * 60;
    if (fix_now_sec / CONST_ONE_DAY_SECONDS - fix_last_sec / CONST_ONE_DAY_SECONDS) {
        CCriticalSectionHelper lock_help(m_lock);
        struct tm *tm;
        time_t y_sec = tv.tv_sec - CONST_ONE_DAY_SECONDS;
        tm = localtime(&y_sec); //yesterday
        char new_file[128] = { 0 };
        snprintf(new_file, 128, "%s.%04d-%02d-%02d", m_log_file.c_str(), tm->tm_year + 1900, tm->tm_mon + 1,
                tm->tm_mday);
        std::string new_file_path = m_log_dir + "/" + new_file;
        if (access(new_file_path.c_str(), F_OK) != 0) {
            rename(m_log_file_path.c_str(), new_file_path.c_str());
            // reopen new log file
            m_fs.close();
            m_fs.open(m_log_file_path.c_str(), std::fstream::out | std::fstream::app);
        }

        delete_old_log(tv);
    }

    m_last_sec = tv.tv_sec;
    return 0;
}

bool CFileAppender::is_inited() {
    return m_is_inited;
}

void CFileAppender::set_retain_day(int rd) {
    m_retain_day = rd;
}

int CFileAppender::delete_old_log(const timeval& tv) {
    if (m_retain_day <= 0) {
        return 0;
    }
    struct timeval old_tv;
    old_tv.tv_sec = tv.tv_sec - m_retain_day * 3600 * 24;
    old_tv.tv_usec = tv.tv_usec;
    char old_file[128] = { 0 };
    struct tm* tm = localtime(&old_tv.tv_sec);
    snprintf(old_file, 128, "%s.%04d-%02d-%02d", m_log_file.c_str(), tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday - 1);
    std::string old_file_path = m_log_dir + "/" + old_file;

    return remove(old_file_path.c_str());
}

int _check_config_file() {
    std::map<std::string, std::string> configs;
    std::string log_config_file = g_dir + "/" + g_config_file;
    get_config_map(log_config_file.c_str(), configs);
    if (configs.empty()) {
        return 0;
    }
    // read log level
    std::string log_level_str = configs["log_level"];
    set_log_level(log_level_str.c_str());

    std::string rd = configs["retain_day"];
    if (!rd.empty()) {
        g_file_appender.set_retain_day(atoi(rd.c_str()));
    }
    // read log file
    std::string dir = configs["log_dir"];
    std::string log_file = configs["log_file"];
    int ret = 0;
    if (!log_file.empty()) {
        use_file_appender = true;
        if (!g_file_appender.is_inited()) {
            ret = g_file_appender.init(dir, log_file);
        }
    }
    return ret;
}

void sigreload(int sig) {
    _check_config_file();
}

std::string _get_show_time(timeval tv) {
    char show_time[64] = { 0 };

    struct tm *tm = localtime(&tv.tv_sec);

    snprintf(show_time, 64, "%04d-%02d-%02d %02d:%02d:%02d.%03d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec, (int) (tv.tv_usec / 1000));
    return std::string(show_time);
}

int _get_log_level(const char *level_str) {
    if (!strcasecmp(level_str, "ERROR")) {
        return ERROR_LEVEL;
    } else if (!strcasecmp(level_str, "WARN")) {
        return WARN_LEVEL;
    } else if (!strcasecmp(level_str, "INFO")) {
        return INFO_LEVEL;
    } else if (!strcasecmp(level_str, "DEBUG")) {
        return DEBUG_LEVEL;
    }
    return DEBUG_LEVEL;
}

void set_log_level(const char *level) {
    log_level = _get_log_level(level);
}

void _log(const char *format, va_list ap) {
    if (!use_file_appender) { // if no config, send log to stdout
        vprintf(format, ap);
        printf("\n");
        return;
    }
    struct timeval now;
    struct timezone tz;
    gettimeofday(&now, &tz);
    std::string fin_format = _get_show_time(now) + " " + format;

    g_file_appender.shift_file_if_need(now, tz);
    char single_log[CONST_MAX_SINGLE_LOG_SIZE] = { 0 };
    g_file_appender.write_log(single_log, fin_format.c_str(), ap);
}

int log_init(const std::string& dir, const std::string& file) {
    g_dir = dir;
    g_config_file = file;
    signal(SIGUSR1, sigreload);
    return _check_config_file();
}

void log_error(const char *format, ...) {
    if (log_level < ERROR_LEVEL) {
        return;
    }
    va_list ap;
    va_start(ap, format);

    _log(format, ap);

    va_end(ap);
}

void log_warn(const char *format, ...) {
    if (log_level < WARN_LEVEL) {
        return;
    }

    va_list ap;
    va_start(ap, format);

    _log(format, ap);

    va_end(ap);
}

void log_info(const char *format, ...) {
    if (log_level < INFO_LEVEL) {
        return;
    }

    va_list ap;
    va_start(ap, format);

    _log(format, ap);

    va_end(ap);
}

void log_debug(const char *format, ...) {
    if (log_level < DEBUG_LEVEL) {
        return;
    }

    va_list ap;
    va_start(ap, format);

    _log(format, ap);

    va_end(ap);
}
