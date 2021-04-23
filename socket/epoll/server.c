#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int main(int argc, char **argv)
{

	int lfd, epollfd;
	int bind_ret;

	int epoll_count;

	struct sockaddr_in addr, client_addr;

	socklen_t client_addr_len = sizeof(client_addr);

	struct epoll_event ev, events[2000];

	char buf[256];

	// 创建监听文件句柄
	lfd = socket(AF_INET, SOCK_STREAM, 0);

	// 绑定端口
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	inet_aton("127.0.0.1", &addr.sin_addr.s_addr);

	bind_ret = bind(lfd, &addr, sizeof(addr));
	if(bind_ret == -1) {
		perror("bind error");
		exit(-1);
	}

	// 监听
	listen(lfd, 2000);

	// epoll create
	epollfd = epoll_create(2000);

	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = lfd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, lfd, &ev);

	// epoll 处理
	while(1) {
	
		// -1 表示阻塞状态
		epoll_count = epoll_wait(epollfd, events, 2000, -1);
		
		int i;

		for(i = 0; i < epoll_count; i++) {
		
			// 新增连接
			if(events[i].data.fd == lfd) {

				printf("新增一个连接 \n");
				
				int acceptfd = accept(lfd, &client_addr, &client_addr_len);
				if(acceptfd == -1) {
					printf("accept fail");
				}

				// 读事件
				ev.events = EPOLLIN|EPOLLET;
				ev.data.fd = acceptfd;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, acceptfd, &ev);

			} else {
			
				// 读事件
				if(events[i].events & EPOLLIN) {

					char buf[256];
					int read_ret = read(events[i].data.fd, &buf, sizeof(buf));

					printf("read_ret = %d \n", read_ret);

					if(read_ret == 0) {
					
						printf("客户端断开连接 \n");

						// 数据读取完成
						epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
						
					} else {
						printf("read data = %s \n", buf);
					}				
	
				}
			
			}

		}


	}

	return 0;

	
}
