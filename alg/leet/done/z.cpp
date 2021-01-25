#include <stdio.h>
#include <string.h>

int main() {
    char num1[1000] = {0};
    char num2[1000] = {0};
    char ans[1000] = {0};
    int len1;
    int len2;
    int len3 = 1000-1;
    int flag = 0;
    int tmp;
    char c1;
    char c2;

    int times;
    scanf("%d", &times);

    for (int i=1; i<=times; i++) {
        scanf("%s %s", num1, num2);
        len1 = strlen(num1)-1;
        len2 = strlen(num2)-1;
        len3 = 1000-1;

        while (len1 >=0 || len2 >= 0) {
            c1 = 0;
            c2 = 0;
            if (len1 >= 0) {
                c1 = num1[len1] - '0';
            }
            if (len2 >= 0) {
                c2 = num2[len2] - '0';
            }
            tmp = c1 + c2 + flag;
            if (tmp >= 10) {
                flag = 1;
                tmp -= 10;
            } else {
                flag = 0;
            }
            ans[len3] = '0' + tmp;
            len1 --;
            len2 --;
            len3 --;
        }
        printf("Case %d:\n%s + %s = %s\n\n", i, num1, num2, ans+len3+1);
    }

    return 0; 
}

