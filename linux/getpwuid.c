#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    struct passwd *pwd;
    printf("%d %d\n", getuid(), geteuid());

    if (argc != 2) {
        fprintf(stderr, "Usage: %s username\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pwd = getpwnam(argv[1]);
    if (pwd == NULL) {
        printf("Not found\n");
        exit(EXIT_FAILURE);
    }

    printf("Name: %s; UID: %ld; HomeDIR: %s\n", pwd->pw_gecos, (long) pwd->pw_uid, pwd->pw_dir);
    exit(EXIT_SUCCESS);
}
