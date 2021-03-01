#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/time.h>

typedef int (*my_connect_func) (struct sockaddr_in *, int);

int my_connect0(struct sockaddr_in *addr, int ms) {
	int sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(sockfd, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) < 0) {
		close(sockfd);
		return -1;
	}

	close(sockfd);

	return 0;
}

int my_connect1(struct sockaddr_in *addr, int ms) {
	int sockfd;
	struct timeval tv;

	tv.tv_sec  = 0;
	tv.tv_usec = ms*1000;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

	if (connect(sockfd, (struct sockaddr *)addr, sizeof(struct sockaddr_in)) < 0) {
		close(sockfd);
		return -1;
	}

	close(sockfd);

	return 0;
}

int my_connect2(struct sockaddr_in *addr, int ms) {
	int sockfd, ret, error;
	unsigned int len;
	struct timeval tv;
	fd_set rset, wset;

	error      = 0;
	tv.tv_sec  = 0;
	tv.tv_usec = ms*1000;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	ret = connect(sockfd, (struct sockaddr *)addr, sizeof(struct sockaddr_in));
	if (ret < 0) {
		if (errno != EINPROGRESS) {
			close(sockfd);
			return -1;
		}
	}

	if (ret == 0) {
		/* success */
		close(sockfd);
		return 0;
	}

	/* in progress */
	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	wset = rset;

	ret = select(sockfd + 1, &rset, &wset, NULL, &tv);
	if (ret == 0) {
		/* no readable or writable socket, timeout */
		close(sockfd);
		errno = ETIMEDOUT;
		return -1;
	}
	else if (ret < 0) {
		/* select error */
		close(sockfd);
		return -1;
	}

	if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) {
		/* check is there any error */
		len = sizeof(error);
		getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);
	}

	if (error) {
		/* connect error */
		close(sockfd);
		errno = error;
		return -1;
	}

	close(sockfd);
	return 0;
}

int main(int argc, char *argv[]) {
	int                  type, ms;
	const char          *ip;
    int                  port;
	struct sockaddr_in   addr;
	my_connect_func      my_connect;

	if (argc < 4) {
		printf("usage: connect <ip> <port> <type> <microseconds>\n");
		return -1;
	}

	ip   = argv[1];
    port = atoi(argv[2]);
	type = atoi(argv[3]);
	ms   = atoi(argv[4]);

	switch (type) {
	case 0:
		my_connect = my_connect0;
		break;
	case 1:
		my_connect = my_connect1;
		break;
	case 2:
		my_connect = my_connect2;
		break;
	default:
		printf("unknow");
		return -1;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);
	inet_pton(AF_INET, ip, &addr.sin_addr);

    struct timeval start;
    gettimeofday(&start, NULL);

	if (my_connect(&addr, ms) < 0) {
		printf("connect failed: %s\n", strerror(errno));
	} else {
		printf("connect success\n");
	}

    struct timeval end;
    gettimeofday(&end, NULL);
    printf("time eslaped: %dms\n", (end.tv_sec-start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)/1000);

	return 0;
}
