#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/listener.h>

void socket_read_cb(struct bufferevent *buffer_event, void *ctx) 
{

	char byte[1024];

	size_t ret = bufferevent_read(buffer_event, byte, sizeof(byte));

	printf("server rec msg : %s \n", byte);

	char msg[] = "我收到了客户端的数据";
	bufferevent_write(buffer_event, msg, strlen(msg) + 1);

}

// 新的客户端连接
void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr socketaddr, int socklen, void *arg) 
{

	printf("accept new conn %d \n", fd);

	struct event_base *base = (struct event_base*)arg;

	// 分配一个新事件
	struct bufferevent *buffer_event = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	//设置回调
	bufferevent_setcb(buffer_event, socket_read_cb, NULL, NULL, NULL);
	bufferevent_enable(buffer_event, EV_READ);

}

int main(int argc, char **argv)
{

	struct sockaddr_in serveraddr;

	// bind
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(1234);

	// 初始化event 框架	
	struct event_base *base = event_base_new();
	printf("base = %p \n", base);

	// 监听套接字
	// bind
	// listen
	// accept
	struct evconnlistener *listener = evconnlistener_new_bind(base, listener_cb, base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1, &serveraddr, sizeof(serveraddr));
	
	

	// 循环事件
	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_base_free(base);

	return 0;

}
