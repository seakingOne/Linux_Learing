#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char **argv)
{

	int fd;
	int ret;
	struct sockaddr_in localaddr; 

	// init socket
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(fd == -1) {
		perror("socket");
		return -1;
	}


	// bind
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(6767);
	inet_pton(AF_INET, "0.0.0.0", &localaddr.sin_addr.s_addr);

	// 绑定
	ret = bind(fd, &localaddr, sizeof(localaddr));
	if(ret == -1){
		perror("bind");
		return -1;
	}

	printf("bind success \n");

	char msg[1024] = {0};
	while(1) {

		ret = recvfrom(fd, &msg, sizeof(msg), 0, NULL, NULL);
		printf("ret = %d \n", ret);
		if(ret < 0) {
			perror("from data fail");
			exit(-1);
		} else {
			printf("recv data = %s \n", msg);
		}

	}

	close(fd);

	return 0;

}
