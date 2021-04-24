#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{

	int fd;
	struct sockaddr_in serveraddr; 

	// init socket
	fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(fd == -1) {
		perror("server error init socket");
		return -1;
	}

	// connet
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(1234);
	
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr.s_addr);

	char buf[1024] = {0};

	while(1) {
	
		printf("请输入:");
		fgets(&buf, sizeof(buf), stdin);

		sendto(fd, &buf, sizeof(buf), 0, &serveraddr, sizeof(serveraddr));

	}

	close(fd);

	return 0;
}
