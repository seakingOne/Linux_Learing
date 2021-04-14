#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 创建n个子进程, 考虑顺序问题
int main()
{

	printf("Begin.....\n");

	int i;
	pid_t pidx;

	for(i = 0; i < 4; i++) 
	{
		pidx = fork();
		if(pidx == 0) 
		{
			printf("I am child%d, pid = %d \n", i, getpid());
			break;
		} else if (pidx > 0)
		{
			printf("I am main, pid = %d \n", getpid());
		}

	}

	sleep(i);
	if (i < 4) {
		printf("I am child %d, will be exit, pid = %d \n", i, getpid());
	}

	printf("End ...... \n");
	return 0;

}
