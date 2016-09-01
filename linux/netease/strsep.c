#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int split(int periods, char* str) {
    char* dst = NULL;
    int   idx = 1;
    int   percent = 0;
    char  buff[128];
    char* tst = buff;

    strcpy(tst, str);
    while (tst && *tst) {
        dst = strsep(&tst, ",");
        percent += round(100*atof(dst));
        idx ++;
    }

    if (idx != periods) {
        printf("periods expired\n");
        return -1;
    }
    int last = 100 - percent;
    if (last < 0) {
        printf("total expired\n");
    }
    sprintf(buff, ",%.2f", last/100.0);
    strcat(str, buff);

    return 0;
}

int main(int argc, char** argv) {
    char tst[64] = "0.20,0.30,0.10,0.20";
    split(5, tst);
    printf("%s\n", tst);
    return 0;
}
