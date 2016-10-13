#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class CTest {
	public:
		CTest() {
			cout << __FUNCTION__ << endl;
		}
		~CTest() {
			cout << __FUNCTION__ << endl;
		}
        void* threadFunc(void* arg) {
            cout << " thread Func " << endl;
        }
};

void* threadFunc(void* para)
{
	CTest goTest;
	int i = 0;
	int* x = (int*)para;

	while (i < 5)
	{
		*x = 1000 + i;
		cout << "i = " << i++ << " x = " << *x << endl;
		sleep(3);
	}

	return NULL;
}


int main(int argc, char** argv)
{
	pthread_t tid;
	int x;

	//pthread_create(&tid, NULL, threadFunc, (void*)&x);
	pthread_create(&tid, NULL, &CTest::threadFunc, (void*)&x);
	pthread_exit(NULL);
	sleep(10);
	exit(0);
}
