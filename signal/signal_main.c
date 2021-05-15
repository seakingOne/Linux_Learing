#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signum)
{

	if(signum == SIGIO) {
		printf("signal : %d \n", signum);
	}

	
}

int main()
{

	signal(SIGIO, handler);
	
	while(1) {
		sleep(10);
	}

	return 0;
}
