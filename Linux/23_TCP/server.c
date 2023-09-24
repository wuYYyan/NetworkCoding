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
	int sockfd, client_sockfd;
	struct sockaddr_in my_addr, client_addr; //sockaddr_in结构体在<netinet/in.h>中定义，见Linux系统编程手册下P429
	int addr_len;
	char welcome[SIZE] = "Welcome to connect to the sever!";

	//1.socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//IPv4: AF_INET，IPv6: AF_INET6，
	//TCP、流式套接字: SOCK_STREAM，UDP、数据包套接字: SOCK_DGRAM

	//2.bind()：为套接字绑定内存空间
	my_addr.sin_family = AF_INET; //IPv4
	my_addr.sin_port = htons(PORT_ID); //htons()函数将主机字节序(大小端模式随主机而异)转换为网络字节序(大端模式)
	my_addr.sin_addr.s_addr = INADDR_ANY; //INADDR_ANY表示监测本地所有IP地址
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	//3.listen()
	listen(sockfd, 10);

	addr_len = sizeof(struct sockaddr); //获取sockaddr结构体的大小，sizeof + 变量类型

	while(1) //服务器一直运行等待
	{
		printf("Server is waiting for client to connect:\n");
		//4.accept()：阻塞等待客户端连接
		client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len); //accept()函数返回一个新的套接字描述符，用于与客户端通信
		printf("Client IP address = %s\n", inet_ntoa(client_addr.sin_addr)); //inet_ntoa()函数将网络字节序二进制的IP地址转换为点分十进制的IP地址
		//5.send()：向客户端发送数据
		send(client_sockfd, welcome, SIZE, 0);
		printf("Disconnect the client request.\n");
		//6.close()：关闭套接字
		close(client_sockfd); //关闭当前客户端通信的套接字
	}

	close(sockfd); //关闭服务器的套接字

	return 0;
}
