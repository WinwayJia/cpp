#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define NUMBER_COUNT (1L << 24)

int main(int argc, char** argv) {
    int fd = open("./data", O_WRONLY|O_CREAT, 0666);
    if (fd < 0) {
        printf("open failed: %s\n", strerror(errno));
        exit(-1);
    }

    char buff[64];
    int len = 0;
    for (int i=0; i<NUMBER_COUNT; i++) {
        len = snprintf(buff, sizeof(buff), "%d\n", rand());
        write(fd, buff, len);
    }
    close(fd);

    return 0;
}
