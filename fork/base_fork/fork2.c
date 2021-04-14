#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 创建n个子进程
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

	printf("End ...... \n");
	return 0;

}
