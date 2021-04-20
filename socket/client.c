#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

void send_data(int socketfd)
{

	int i;

	for(i = 0; i < 5; i++) {
	
		char buf[256];

		printf("please input data: \n");
		fgets(buf, sizeof(buf), stdin);

		// send
		write(socketfd, buf, strlen(buf));

		// get data from server
		//int len = read(socketfd, buf, strlen(buf));
		//if(len < 0) {
		//	printf("error");
		//	exit(-1);
		//}

		//printf("client recv: %s \n", buf);

	}

}

int main(int argc, char **argv)
{

	int fd;
	struct sockaddr_in serveraddr; 

	// init socket
	fd = socket(AF_INET, SOCK_STREAM, 0);

	if(fd == -1) {
		printf("server error init socket");
		return -1;
	}

	// connet
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(1234);
	
	inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr.s_addr);

	connect(fd, &serveraddr, sizeof(serveraddr));

	send_data(fd);

	close(fd);
}
