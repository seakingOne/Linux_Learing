#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *mythread(void)
{

	printf("I am thread, tid = %lu \n", pthread_self());

	//pthread_exit(NULL);

	//return (void*)100;
	return NULL;
}

int main()
{

	void *status;

	pthread_t pt;

	pthread_create(&pt, NULL, (void*) mythread, NULL);

	//线程自身强制退出
	//pthread_exit(0);
	
	//杀死线程
	pthread_cancel(pt);

	//main等待子线程完成
	pthread_join(pt, &status);

	printf("status = %d \n", (int)status);


	return 0;

}
