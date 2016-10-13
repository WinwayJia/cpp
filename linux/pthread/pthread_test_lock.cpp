#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "MutexLock.h"

using namespace std;
int g_x = 0;

CMutexLock g_lock;

void* threadFunc(void* para)
{
	while (true)
	{
		g_lock.Lock();
		cout << "Here" << endl;
		g_lock.Lock();
		cout << "Here again" << endl;
		if (g_x < 1000)
		{
			usleep(100);
			cout << "sale g_x = " << g_x << endl;
			g_x ++;
		}
		else 
		{
			g_lock.Unlock();
			g_lock.Unlock();
			break;
		}
		g_lock.Unlock();
		g_lock.Unlock();
	}

	return NULL;
}


int main(int argc, char** argv)
{
	pthread_t tid;
	int x;

	pthread_create(&tid, NULL, threadFunc, (void*)&x);
	pthread_create(&tid, NULL, threadFunc, (void*)&x);
	pthread_create(&tid, NULL, threadFunc, (void*)&x);
	pthread_join(tid, NULL);

	return 0;
}
