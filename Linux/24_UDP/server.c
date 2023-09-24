#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT_ID	8800
#define SIZE	100

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr, client_addr;
	int addr_len;
	char buf[SIZE];

	//1.socket()
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	//2.bind()
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT_ID);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	addr_len = sizeof(struct sockaddr);

	while(1)
	{
		printf("Server is waiting for client to connect:\n");
		//4.recvfrom()：阻塞等待客户端连接
		recvfrom(sockfd, buf, SIZE, 0, (struct sockaddr *)&client_addr, &addr_len); 
		//UDP不面向连接，所以在形参中需要传递客户端的地址，否则不知道从哪里接收数据
		printf("Server receive from client: %s\n", buf);
	}

	close(sockfd); //不面向连接，因此只需要关闭服务器套接字

	return 0;
}
