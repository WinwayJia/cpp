#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct zend_string {
    long long rc;
    int       len;
    char      val[1];
} zend_string;

#define Z_STRLEN_P(op) (op->len)
#define Z_STRVAL_P(op) (op->val)

zend_string* create_zend_string(const char* src, int len)
/*{
    zend_string* zs = malloc(sizeof(zend_string) + len + 1);
    zs->len = len;
    memcpy(zs->val, src, len);

    return zs;
}
*/
{
    zend_string* zs = malloc((int)(((zend_string*)0)->val) + len + 1);
    zs->len = len;

    strcpy(zs->val, src);

    return zs;
}

int main(int argc, char** argv)
{
    printf("sizeof(zend_string) =%lu\n", sizeof(zend_string));
    printf("offset = %llu\n", (unsigned long long)(((zend_string*)0)->val));

    // zend_string* zs = create_zend_string("Hello, World", 12);  
    zend_string* zs = create_zend_string("0", 1);  

    if (Z_STRLEN_P(zs) == 0 || (Z_STRLEN_P(zs) == 1 && Z_STRVAL_P(zs)[0] == '0')) {
        printf("reach here %d %c\n", Z_STRLEN_P(zs), Z_STRVAL_P(zs)[0]);
    }

    return 0;
}
