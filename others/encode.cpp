#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include "Base64.h"

using namespace std;

void usage(const char* arg)
{
    cout << arg << "{encode|decode} parameter" << endl;
}

int main(int argc, char** argv) 
{
    string str;
    Base64 b;
    string out;
    string rst;
    char* ptr = NULL;

    if (argc < 3) {
        usage(argv[0]);
        exit(0);
    }
    
    if (!strcasecmp(argv[1], "encode")) {
        for (ptr = argv[2]; *ptr; ptr++) {
            str += ~(*ptr+2);
        }
        cout << str << endl;
        b.encode(str,  out, false);
        cout << out << endl;

        rst = out.substr(0, out.find('=')); // erase = 
        cout << rst << endl;
    } else if (!strcasecmp(argv[1], "decode")) {
        str = argv[2];
        int num = str.size() % 4;
        if (num == 1) {

        } else if (num == 2) {
           str += "=="; 
        } else if (num == 3) {
            str += "=";
        }
        b.decode(str, out);
        string::iterator it;
        for (it = out.begin(); it != out.end(); it++) {
            *it = ~(*it)-2;
        }
        cout << out << endl;
    } else {
        cout << "invalid parameter" << endl;
        usage(argv[0]);
        exit(-1);
    }


    return 0;
}
