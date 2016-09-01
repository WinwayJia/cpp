// output accts current
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char* acct_cycle="201402";
char* DISCOUNT_FEE="1000";

int deal(char* PERIODS, char *ACTIVITY_ID, char* SPREAD_CYCLES, char* SPREAD_ACCTS, char* CURRENT) {
    char buff[256] = {0};
    char curr[16] = {0};
    char tmp[16] = {0};
    char* tst = buff;
    char* dst = NULL;
    int idx = 1;
    int alen = 0;
    int clen = 0;
    float total = 0;
    int acy = atoi(acct_cycle);
    int year = acy / 100;
    int mon = acy % 100;
    float last = 0.0f;
    int disfee = atol(DISCOUNT_FEE);
    strcpy(tst, ACTIVITY_ID);

    while (tst && *tst) {
        dst = strsep(&tst, ",");

        if (!curr[0]) {
            sprintf(curr, "%d", (int)round(disfee*atof(dst)));
            strcpy(CURRENT, curr);
            alen += sprintf(SPREAD_ACCTS, "%s,", curr);
        } else {
            alen += sprintf(SPREAD_ACCTS+alen, "%d,", (int)round(disfee*atof(dst)));
        }

        clen += sprintf(SPREAD_CYCLES+clen, "%04d%02d,", year, mon);
        if (++ mon > 12) {
            year ++; mon = 1;
        }

        idx ++;
        total += atof(dst);
    }

    if (idx != atoi(PERIODS)) 
        return -1;
    last = 1.0 - total;
    if (last < 0.0) 
        return -1;
    
    sprintf(tmp, ",%.2f", last);
    strcat(ACTIVITY_ID, tmp);
    alen += sprintf(SPREAD_ACCTS+alen, "%d,", (int)round(disfee*last));
    clen += sprintf(SPREAD_CYCLES+clen, "%04d%02d,", year, mon);
    SPREAD_CYCLES[clen-1] = '\0';
    SPREAD_ACCTS[alen-1] = '\0';

    return 0;
}

int main(int argc, char** argv) {
    char* PERIODS = "12";
    char ACTIVITY_ID[128] = "0.1,0.1,0.1,0.1,0.1,0.05,0.05,0.05,0.05,0.05,0.05";
    char SPREAD_CYCLES[256];
    char SPREAD_ACCTS[256];
    char CURRENT[128];
    if (deal(PERIODS, ACTIVITY_ID, SPREAD_CYCLES, SPREAD_ACCTS, CURRENT) < 0) {
        printf("meeting error\n");
    } else {
        printf("ACTIVITY_ID: %s\nCYCLES: %s\nACCTS: %s\nCURRENT: %s\n", ACTIVITY_ID, SPREAD_CYCLES, SPREAD_ACCTS, CURRENT);
    }

    return 0;
}
