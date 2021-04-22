#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int main(int argc, char **argv)
{

	int lfd, clientfd;
	int ret;
	struct sockaddr_in serveraddr, clientaddr; 
	socklen_t clientsize;

	lfd = socket(AF_INET, SOCK_STREAM, 0);

	if(lfd == -1) {
		perror("socket");
		return -1;
	}

	//setnonblocking(lfd);

	// epoll 处理
	int epollfd = epoll_create(60);
	// 注册事件
	struct epoll_event ev, events[60];
	ev.data.fd = lfd;
	// 读事件
	ev.events = EPOLLIN|EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, lfd, &ev);

	// bind
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(1234);

	//端口重用
	int value = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	ret = bind(lfd, &serveraddr, sizeof(serveraddr));
	if(ret == -1){
		perror("bind");
		return -1;
	}

	// listen
	listen(lfd, 60);

	clientsize = sizeof(clientaddr);

	while(1) {

		// 等待事件发生
		int epollnums = epoll_wait(epollfd, events, 60, 500);

		int i;

		printf("events = %d, lfd = %d \n", events[0], lfd);

		for(i = 0; i < epollnums; i++) {
			// 新增连接
			if(events[i].data.fd == lfd) {
				int connfd = accept(lfd, &clientaddr, clientsize);

				printf("add new fd....");

				//注册
				ev.data.fd = connfd;
				ev.events = EPOLLIN|EPOLLET;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, lfd, &ev);

			} 
			// 如果是读事件
			else if (events[i].events & EPOLLIN) {

				char line[256];
				int socketfd = events[i].data.fd;

				if(socketfd < 0) {
					continue;
				}

				int ret = read(socketfd, line, strlen(line));

				// 数据发送完毕
				if(ret == 0) {

					printf("read data = %s", line);

					close(socketfd);
					events[i].data.fd = -1;
				}

				//数据读取完成之后可以写入
				ev.data.fd = socketfd;
				ev.events = EPOLLOUT|EPOLLET;
				epoll_ctl(epollfd, EPOLL_CTL_MOD, lfd, &ev);
				
			 } 
			 // 如果是写事件
			 else if (events[i].events & EPOLLOUT) {
			 
				 char line[256];

				 int socketfd = events[i].data.fd;
				 write(socketfd, line, strlen(line));

				 //数据写入之后可以读取
				 ev.data.fd = socketfd;
				 ev.events = EPOLLIN|EPOLLET;
				 epoll_ctl(epollfd, EPOLL_CTL_MOD, lfd, &ev);
			 
			 }
		}

	}


}
