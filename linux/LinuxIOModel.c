#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <aio.h>

#define ERROR(str)          \
    do {                    \
        fprintf(stderr, "[%s:%d]: %s:%s\n", __FILE__, __LINE__, strerror(errno), str); \
        exit(errno);        \
    } while(0)

#define INFO(str)          \
    do {                    \
        fprintf(stdout, "[%s:%d]: %s\n", __FILE__, __LINE__, str); \
    } while(0)

void signalHandler(int signo) {
    INFO("catch signal");
}
const int SIZE = 1024;
// recv 1024B from server
int synchronousBlock(int sock) {
    char buff[SIZE];
    int left = SIZE;
    int recvd = 0;
    int ret = 0;

    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) & ~O_NONBLOCK);
    while (left > 0) {
        ret = recv(sock, buff+recvd, left, 0);
        INFO("recving....");
        if (ret > 0) {
            recvd += ret;
            left -= ret;
        } else {
            if (errno == EINTR) {
                continue;
            }
            break;
        }
    }

    return recvd;
}

int synchronousNoneBlock(int sock) {
    char buff[SIZE];
    int left = SIZE;
    int recvd = 0;
    int ret = 0;

    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
    while (left > 0) {
        ret = recv(sock, buff+recvd, left, 0);
        INFO("recving....");
        if (ret > 0) {
            recvd += ret;
            left -= ret;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                continue;
            }
            break;
        }
    }

    return recvd;
}

int AsynchronousBlock(int sock) {

}

int AsynchronousNoneBlock(int sock) {

}

int initSock() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        ERROR("");        
    }
    signal(SIGUSR1, signalHandler);
    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) & ~O_NONBLOCK);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(60000);
    addr.sin_addr.s_addr = inet_addr("192.168.159.1");

    if (connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
        ERROR("");
    }

    return sock;
}

int main(int argc, char** argv) {
    int sock = initSock();

    char buff[1024];
    if (send(sock, "Hello", 5, 0) != 5) {
        ERROR("");
    }

//    synchronousBlock(sock);
    synchronousNoneBlock(sock);

    close(sock);
    INFO("exit.....");

    return 0;
}
