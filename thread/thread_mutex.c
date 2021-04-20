#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int count;
pthread_mutex_t pmt;

void *mythread(void)
{

	int i;
	pthread_mutex_lock(&pmt);

	for(i = 0; i < 10; i++) {
		printf("I am thread, tid = %lu , count = %d \n", pthread_self(), ++count);
	}
	//pthread_exit(NULL);

	//return (void*)100;
	
	pthread_mutex_unlock(&pmt);

	return NULL;
}

int main()
{

	void *status;

	pthread_t pt1, pt2;

	pthread_mutex_init(&pmt, 0);

	pthread_create(&pt1, NULL, (void*) mythread, NULL);
	pthread_create(&pt2, NULL, (void*) mythread, NULL);

	//main等待子线程完成
	pthread_join(pt1, &status);
	pthread_join(pt2, &status);

	pthread_mutex_destroy(&pmt);


	return 0;

}
