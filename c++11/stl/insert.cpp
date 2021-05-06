#include <stdio.h>
#include <string.h>

#include <iostream>
#include <map>

using namespace std;

#define DEF_ERROR_MSG_LEN (256)
struct STRU_ERROR_DESCRIPT {
    int miErrorCode;
    int miChangeType;
    char mszErrorDescript[DEF_ERROR_MSG_LEN];
    int* mpInt;

    STRU_ERROR_DESCRIPT() { init(); }
    ~STRU_ERROR_DESCRIPT() { cout << "strcpy(mszErrorDescript" << endl; }
    void init() {
        miErrorCode = 0;
        miChangeType = 0;
        memset(mszErrorDescript, 0, DEF_ERROR_MSG_LEN);
    }
    /*
        const STRU_ERROR_DESCRIPT & operator=(const STRU_ERROR_DESCRIPT& v)
        {
            cout << "in operator=" << endl;
            this->miErrorCode = v.miErrorCode;
            this->miChangeType = v.miChangeType;
            //strncpy(mszErrorDescript, v.mszErrorDescript, DEF_ERROR_MSG_LEN);
        }
    */
};

map<int, STRU_ERROR_DESCRIPT> goMap;

int test(int x) {
    STRU_ERROR_DESCRIPT loErrDesc;
    loErrDesc.miErrorCode = x;
    loErrDesc.miChangeType = x;
    sprintf(loErrDesc.mszErrorDescript, "Test_%d", x);
    // goMap.insert(make_pair(x, loErrDesc));
    goMap[x] = loErrDesc;
    printf("test: %p %p\n", loErrDesc.mszErrorDescript, loErrDesc.mpInt);

    return 0;
}

int overwrite_stack() {
    char lszBuff[1024];
    memset(lszBuff, 0, 1024);

    return 0;
}

int main() {
    test(1);
    test(2);

    for (map<int, STRU_ERROR_DESCRIPT>::iterator x = goMap.begin();
         x != goMap.end(); x++) {
        cout << "main: " << x->first << " -> " << x->second.mszErrorDescript
             << endl;
        printf("main: %p %p\n", x->second.mszErrorDescript, x->second.mpInt);
    }
    test(2);

    return 0;
}
