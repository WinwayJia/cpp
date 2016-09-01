#include <string>
#include <stdlib.h>
#include <libssh2.h>
//#include <
namespace util
{
using namespace std;

class ssh2_cmd {
public:
    enum ssh2_cmd_status
    {
        IDLE,
        CONNECTED,
        LOGINED,
    };
    ssh2_cmd();
    ssh2_cmd(const string& host_, const string& user_, const string& passwd_);
    bool openSession(const string&,const string&, const string&, const int& port);
    void closeSession(void);
    void disconnect();
    ~ssh2_cmd();

    void set_host(const string& host_);
    void set_user(const string& user_);
    void set_passwd(const string& passwd_);

    char* response();
    bool send_cmd(const string& cmd);
    
    void reset();
private:
    //bool socket_wait();
    // Connect to ssh server.
    bool connectTo(const string& ,const string& ,const string& , const int& port);
    string host;
    string user;
    string passwd;
    //string pub_key;
    //string pri_key;
    //string passphrase;
    ssh2_cmd_status status;

    int sock_fd;
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    bool connected;
    
    int exitcode;
};
}
