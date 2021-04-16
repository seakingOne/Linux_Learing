#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

	int pipefd[2];

	// 创建通道
	pipe(pipefd);

	pid_t pid = fork();

	if(pid == 0) {

		printf("I am child, pid = %d \n", getpid());
		
		//单通道
		// 关闭写
		close(pipefd[1]);

		char buf[256];
		// 开始读取
		while(read(pipefd[0], &buf, 1)) {
			write(STDOUT_FILENO, &buf, 1);
		}

		//write(STDOUT_FILENO, "\n", 1);

		close(pipefd[0]);

	} else if (pid > 0) {

		//关闭读端
		close(pipefd[0]);
		char text[] = "hello world \n";
		write(pipefd[1], text, strlen(text));
		close(pipefd[1]);

		sleep(2);
	}
	
	return 0;

}
