//
// Created by jiawh on 16-9-18.
//



#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char** argv) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket failed.");
    }

    int flag = 1;
    socklen_t len;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, len);

    struct sockaddr_in svr_addr;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = INADDR_ANY;
    svr_addr.sin_port = htons(9000);
    int ret = bind(sock, (struct sockaddr*)&svr_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        perror("bind failed.");
    }

    listen(sock, 512) ;

    struct sockaddr_in addr;
    char buff[1024] = {0};
    while (true) {
        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("accept failed.");
        }
        ret = recv(client, buff, 1024, 0);
        if (ret < 0) {
            perror("recv failed");
            break;
        }
        printf("%s", buff);
        send(client, buff, ret, 0);
        close(client);
    }

    close(sock);
}
