#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT_ID	8800
#define SIZE	100

//./client IP  : ./client 192.168.0.10
int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in server_addr;
	char buf[SIZE];
	int i;

	if(argc < 2)
	{
		printf("Usage: ./client [server IP address]\n");
		exit(1);
	}

	//1.socket()
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_ID);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]); //传递服务器的地址

	//客户端向服务器发送数字0~9
	for(i = 0; i < 10; i++)
	{
		sprintf(buf, "%d\n", i); //将内容输出到buf中
		sendto(sockfd, buf, SIZE, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
		printf("Client sends to server %s: %s\n", argv[1], buf);
		sleep(1);
	}

	close(sockfd);

	return 0;
}
