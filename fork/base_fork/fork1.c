#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 简单测试，回返回两次end调用
int main()
{

	printf("Begin.....\n");
	pid_t pid = fork();
	if(pid < 0) {
		perror("fork error");
		exit(1);
	}

	if(pid == 0) {
		printf("I am child, pid = %d \n", getpid());
	}

	if(pid > 0) {
		// 父进程流程
		printf("I am main, pid = %d \n", getpid());
		sleep(1);
	}

	printf("End ....\n");
	return 0;

}
