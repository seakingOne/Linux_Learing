#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{

	int fd;
	int ret;
	struct sockaddr_in serveraddr; 

	// init socket
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(fd == -1) {
		perror("socket");
		return -1;
	}


	// bind
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(1234);
	ret = bind(fd, &serveraddr, sizeof(serveraddr));

	if(ret < 0) {
		perror("bind fail");
		exit(-1);
	}

	// 初始化客户端信息
	struct sockaddr_in clientaddr;
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(6767);
	clientaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	//inet_pton(AF_INET, "16.155.199.255", &clientaddr.sin_addr.s_addr);

	//设置广播类型
	int value = 1;
	setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &value, sizeof(value));

	char msg[1024] = {0};
	while(1) {

		printf("请输入: \n");
		fgets(&msg, sizeof(msg), stdin);
		sendto(fd, &msg, strlen(msg) + 1, 0, &clientaddr, sizeof(clientaddr));

	}


	close(fd);

	return 0;

}
