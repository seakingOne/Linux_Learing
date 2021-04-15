#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

	int status;
	pid_t pid = fork();

	if(pid == 0) {
		printf("I am child pid = %d \n", getpid());
		sleep(2);	
	} else if(pid > 0) {
		//wait的使用
		//wait(NULL);
		waitpid(pid, &status, 0);
		printf("I am main pid = %d \n", getpid());
	}

	printf("exec finsh... pid=%d \n", getpid());
	return 0;

}
