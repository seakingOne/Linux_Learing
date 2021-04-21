#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

void read_data(int socketfd)
{
	char buf[256];

	if(read(socketfd, &buf, sizeof(buf)) > 0){
		printf("server recv: %s \n", buf);
	}

}

int main(int argc, char **argv)
{

	int fd, clientfd;
	int ret;
	struct sockaddr_in serveraddr, clientaddr; 
	socklen_t client;

	// init socket
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if(fd == -1) {
		perror("socket");
		printf("server error init socket");
		return -1;
	}


	// bind
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(1234);

	//端口重用
	int value = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	ret = bind(fd, &serveraddr, sizeof(serveraddr));
	if(ret == -1){
		perror("bind");
		printf("server error init socket");
		return -1;
	}

	// listen
	listen(fd, 60);

	client = sizeof(clientaddr);
	// accept
	clientfd = accept(fd, &clientaddr, &client);

	// deal data
	int time = 0;
	while(1) {
		// read data
		read_data(clientfd);

		time++;
		
		printf("this time is : %d \n", time);

		if(time > 5) {
			break;
		}

	}

	close(fd);
	close(clientfd);

}
