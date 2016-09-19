#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "EpollCtl.h"

int do_connect(const char* ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed.");
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    socklen_t  len = sizeof(struct sockaddr_in);
    int ret = connect(sock, (struct sockaddr*)&addr, len);
    if (ret < 0) {
        perror("connect failed");
        return -1;
    }

    return sock;
}

void callback_read(int fd, void* buff, int len) {
    write(1, buff, len);
}

int main() {
    EpollCtl epollCtl;

    int sock = do_connect("127.0.0.1", 9000);
    epollCtl.add_fd(sock, callback_read);

    epollCtl.run();
    send(sock, "Hello", 5, 0);

    while (true) {
        sleep(1);
    }
}