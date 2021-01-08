#include <iostream>  
#include <cstring>
#include <algorithm>  
#include <iostream>
#include <stdio.h>

using namespace std;

char s[1000];
char s_new[2000];
int p[2000];

int Init() {
    int len = strlen(s);
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;

    for (int i = 0; i < len; i++) {
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }

    s_new[j] = '\0';  // 别忘了哦
    
    return j;  // 返回 s_new 的长度
}

int Manacher() {
    int len = Init();  // 取得新字符串长度并完成向 s_new 的转换
    int max_len = -1;  // 最长回文长度

    int id;
    int max = 0;

    for (int i = 1; i < len; i++) {
        if (i < max) {
            p[i] = min(p[2 * id - i], max - i);  // 需搞清楚上面那张图含义, max 和 2*id-i 的含义
        } else {
            p[i] = 1;
        }

        while (s_new[i - p[i]] == s_new[i + p[i]]) { // 不需边界判断，因为左有'$',右有'\0'
            p[i]++;
        }

        // 我们每走一步 i，都要和 max 比较，我们希望 max 尽可能的远，这样才能更有机会执行 if (i < max)这句代码，从而提高效率
        if (max < i + p[i]) {
            id = i;
            max = i + p[i];
        }

        max_len = max(max_len, p[i] - 1);
    }

    cout << "p[i]:";
    for (int i=0; i<len; i++) {
        printf("p[%02d]=%02d\n", i, p[i]);
    }
    cout << endl;

    return max_len;
}

int main() {
    while (printf("请输入字符串：\n")) {
        scanf("%s", s);
        printf("最长回文长度为 %d\n\n", Manacher());
    }
    return 0;
}
