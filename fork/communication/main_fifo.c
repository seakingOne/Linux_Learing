#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "./myfifo"

//初始化fifo文件 mkfifo name
int main() {

	int pipefd[2];

	// 创建通道
	pipe(pipefd);

	pid_t pid = fork();

	if(pid == 0) {

		printf("I am child, pid = %d \n", getpid());
		

		int readfd = open(FIFO_PATH, O_RDONLY);

		// 读取文件
		char buf[256];

		// 开始读取
		while(read(readfd, &buf, 1)) {
			write(STDOUT_FILENO, &buf, 1);
		}

		close(readfd);

	} else if (pid > 0) {

		char text[] = "hello world \n";

		int wfd = open(FIFO_PATH, O_WRONLY);

		write(wfd, text, strlen(text));
		close(wfd);

		sleep(2);
	}
	
	return 0;

}
