#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#define PORT_ID	8800
#define SIZE	100

void *thread_function(void *arg);
struct sockaddr_in client_addr;
int client_sockfd;
char welcome[SIZE] = "Welcome to connect to the sever!";

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr;
	int addr_len;
	pthread_t pthread;

	//1.socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//2.bind()
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT_ID);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	//3.listen()
	listen(sockfd, 10);

	addr_len = sizeof(struct sockaddr);

	while(1)
	{
		printf("Server is waiting for client to connect:\n");
		//4.accept()：阻塞并等待客户端的连接请求
		client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
		pthread_create(&pthread, NULL, thread_function, NULL); 
		//当有客户端连接时才创建一个线程，不会造成资源的浪费，但可能会造成线程的频繁创建和销毁，响应时间较长
		//创建线程之后，到线程处理函数中进行数据的收发与客户端的相应
	}

	close(sockfd);

	return 0;
}

void *thread_function(void *arg)
{
	printf("Client IP address = %s\n", inet_ntoa(client_addr.sin_addr));
	//5.send()
	send(client_sockfd, welcome, SIZE, 0);
	printf("Disconnect the client request.\n");
	close(client_sockfd);
	pthread_exit(NULL);

	return NULL;
}
