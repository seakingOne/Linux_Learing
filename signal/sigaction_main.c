#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig)
{

	printf("oh, got a signal %d \n", sig);

}

int main() 
{

	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, 0);

	while(1) {
		sleep(5);
	}

}
