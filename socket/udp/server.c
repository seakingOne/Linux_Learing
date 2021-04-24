#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{

	int fd; 
	int ret;
	struct sockaddr_in serveraddr, clientaddr; 
	socklen_t client;

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
	if(ret == -1){
		perror("bind");
		return -1;
	}


	client = sizeof(clientaddr);
	char buf[1024] = {0};

	while(1) {
		ret = recvfrom(fd, &buf, sizeof(buf), 0, &clientaddr, &client);
		if(ret == -1) {
			perror("recv");
			return -1;
		}
		
		printf("buf = %s \n", buf);
		memset(buf, 0, sizeof(buf));
	}


	close(fd);
	
}
