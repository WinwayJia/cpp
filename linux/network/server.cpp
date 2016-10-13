//
// Created by jiawh on 16-9-18.
//



#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void* client_thread(void* arg) {
    char buff[1024] = {0};
    int client = (int)((int*)arg);

    printf("fd: %d", client);
    while (true) {
        int ret = recv(client, buff, 1024, 0);
        if (ret < 0) {
            perror("recv failed");
            break;
        }
        printf("%s", buff);
        send(client, buff, ret, 0);
    }
    close(client);

    return NULL;
}

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
    while (true) {
        int client = accept(sock, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("accept failed.");
        }
        printf("accept client: %s:%d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        pthread_t tid;
        int *ptr = (int*)client;
        pthread_create(&tid, NULL, client_thread, (void*)ptr);
    }

    close(sock);
}
