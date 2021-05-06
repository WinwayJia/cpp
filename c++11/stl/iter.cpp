#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <set>

using namespace std;

set<int> goSet;
void* threadFun(void* para) {
    for (int i = 0; i < 10; i++) {
        goSet.insert(i);
        sleep(1);
    }
    for (int i = 5; i < 10; i++) {
        goSet.erase(i);
        sleep(1);
    }
}

int main(int argc, char** argv) {
    pthread_t tid;
    pthread_create(&tid, NULL, threadFun, NULL);

    do {
        for (set<int>::iterator iter = goSet.begin(); iter != goSet.end();
             iter++) {
            cout << *iter << " ";
            sleep(1);
        }
        cout << endl;
        sleep(3);
    } while (1);

    return 0;
}
