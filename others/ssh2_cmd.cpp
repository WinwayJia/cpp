#include "ssh2_cmd.h"
#include <sys/types.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <libssh2.h>
//#include "common.h"
namespace util
{
using std::ostringstream;
using std::cout;
using std::clog;
using namespace util;
#define dout cout
    class bad_file : public exception {
        public:
    enum bad_type
            {
              bad_stat,    ///<Error while stat a file.
              bad_lstat,    ///<Error while lstat a file.
              bad_statfs,    ///<Error while statfs a file.
              bad_sock,    ///<Error using socket.
              bad_open,    ///<Error while open a file.
              bad_seek,    ///<Error while seek a file.
              bad_read,    ///<Error while read from a file.
              bad_write,    ///<Error while write to a file.
              bad_flush,    ///<Error while flush a file.
              bad_close,    ///<Error while close a file.
              bad_remove,    //<Popen error.
            };
        bad_file(const string& file, int line, int sys_code_, int error_code_, const string& obj = "") throw() {
            sys_code = sys_code_;
            error_code = error_code_;
            what_ = obj;
        }
        ~bad_file() throw() {}
        const char* error_msg() const throw() {}
        const char* what() const throw() {return what_.c_str();}

        private:
        int sys_code;
        int error_code;    ///<The error code.
        string what_;    ///<The error message.
        static const char* messages[];    ///<The error content.
    };
ssh2_cmd::ssh2_cmd()
{
    sock_fd = -1;
    session = NULL;
    connected = false;
    channel = NULL;
}

ssh2_cmd::ssh2_cmd(const string& host_, const string& user_, const string& passwd_)
{
    host = host_;
    user = user_;
    passwd = passwd_;
    
    sock_fd = -1;
    session = NULL;
    connected = false;
    channel = NULL;
}

ssh2_cmd::~ssh2_cmd()
{
    this->closeSession();
}

void ssh2_cmd::disconnect()
{
    if (session){
        libssh2_session_disconnect(session,"Normal Shutdown, Thank you for playing");
        libssh2_session_free(session);
    }
    ::close(sock_fd);
    connected = false;
    libssh2_exit();
}

bool ssh2_cmd::openSession(const string& host_,const string& userName, const string& password, const int& port)
{
    if (this->connected)
        return true;
    if (!this->connectTo(host_,userName, password, port))
        return false;

    return true;
}

void ssh2_cmd::closeSession(void) {
    if (this->connected) {
        this->disconnect();
    }
}

bool ssh2_cmd::connectTo(const string& host_,const string& uname,const string& password, const int& port)
{
    dout<<"["<<__FILE__<<"]["<<__LINE__<<"] connectTo() host_ = ["<<host_<<"] uname = ["<<uname<<"] password = ["<<password<<"] port = ["<<port<<"]"<<std::endl;

    int rc;
    sockaddr_in sin;
    host = host_;
    user = uname;
    passwd = password;
    
    memset(&sin, 0, sizeof(sin));
    rc = libssh2_init(0);
    if (rc != 0) {
        bad_file(__FILE__, __LINE__, 172, bad_file::bad_sock, strerror(errno));
        return false;
    }
 
    unsigned long hostaddr;
    hostaddr = inet_addr(host_.c_str());
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = hostaddr;
    sock_fd = socket(sin.sin_family, SOCK_STREAM, 0);
    dout<<"In connect,sock_fd = ["<<sock_fd<<"]"<<std::endl;
    if (sock_fd == -1) {
         bad_file(__FILE__, __LINE__, 173, bad_file::bad_sock, strerror(errno));
         return false;
    }
    
    if (::connect(sock_fd, (struct sockaddr*)(&sin), sizeof(struct sockaddr_in)) != 0) {
         bad_file(__FILE__, __LINE__, 174, bad_file::bad_sock, strerror(errno));
         return false;
    }
    
    
    session = libssh2_session_init();
    if (session == NULL)
     {
        ::close(sock_fd);
        bad_file(__FILE__, __LINE__, 300, bad_file::bad_sock, strerror(errno));
        return false;
    }
    
    libssh2_session_set_blocking(session, 1);

    rc = libssh2_session_handshake(session, sock_fd);
    if (rc) {
        dout << "["<<__FILE__<<"] LINE["<<__LINE__<<"]" << "Failure establishing SSH session: %d" << rc << std::endl;
        return false;
    }
    
    if (libssh2_userauth_password(session, user.c_str(), passwd.c_str())) {
        dout<<"Authentication by password failed"<<endl;   
        ::close(sock_fd);
        bad_file(__FILE__, __LINE__, 302, bad_file::bad_sock, strerror(errno));  
        return false;
    }    

    connected = true;
    cout<<"CONNECTED:"<<sock_fd<<endl;
    
    return true;
}

void ssh2_cmd::set_host(const string& host_)
{
    host = host_;
}

void ssh2_cmd::set_user(const string& user_)
{
    user = user_;
}

void ssh2_cmd::set_passwd(const string& passwd_)
{
    passwd = passwd_;
}
/*
bool ssh2_cmd::socket_wait()
{
    struct timeval timeout;
    int rc;
    fd_set readfd;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    FD_ZERO(&fd);

    FD_SET(sock_fd, &readfd);

    rc = select(sock_fd + 1, readfd, NULL, NULL, &timeout);

    return rc;
}
*/
// Send a command and wait for expected response
bool ssh2_cmd::send_cmd(const string& cmd)
{
    int bytecount = 0;
    int rc;
    char buffer[0x4000];
    char* ptr = buffer;
    
    dout << cmd << std::endl;
    
    channel = libssh2_channel_open_session(session);
    if (channel == NULL) {
        dout << "["<<__FILE__<<"] LINE["<<__LINE__<<"]" << "libssh2_channel_open_session Error" << std::endl;
        return false;
    }
    rc = libssh2_channel_exec(channel, cmd.c_str());
    if( rc != 0 ) {
        dout << "["<<__FILE__<<"] LINE["<<__LINE__<<"]" << "libssh2_channel_exec Error" << std::endl;
        int ret = libssh2_session_last_error(session, &ptr, &rc, 0);
        return false;
    }
    for( ;; ) {
        do {
            rc = libssh2_channel_read( channel, buffer, sizeof(buffer) );
            if( rc > 0 ) {
                int i;
                bytecount += rc;
                dout << "We read:" << std::endl;
                for( i=0; i < rc; ++i )
                    fputc( buffer[i], stdout);
                fprintf(stderr, "\n");
            }
            else {
                if( rc != LIBSSH2_ERROR_EAGAIN )
                    dout << "["<<__FILE__<<"] LINE["<<__LINE__<<"]" << "libssh2_channel_read returned" << std::endl;
            }
        } while( rc > 0 );

        if( rc == LIBSSH2_ERROR_EAGAIN ) {
            //socket_wait();
        }
        else
            break;
    }
    libssh2_channel_close(channel);
    
    return true;
}

void ssh2_cmd::reset()
{
    this->disconnect();
}

}


using namespace util;
int main(int argc, char** argv)
{
    ssh2_cmd sh;
    //sh.openSession("10.1.249.34", "tstchc01", "Linuxtst_4321", 22);
    sh.openSession("127.0.0.1", "jiawh", "111111", 22);
//    sh.send_cmd("gzip -d t.cp.gz");

    sh.send_cmd("whoami");

    return 0;
}
