#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT_ID	8800
#define SIZE	100

//run model£º./client IP£¬ÀýÈç: ./client 192.168.0.10
int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in server_addr;
	char buf[SIZE];

	if(argc < 2)
	{
		printf("Usage: ./client [server IP address]\n");
		exit(1);
	}

	// 1.socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// 2.connect()
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_ID);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

	recv(sockfd, buf, SIZE, 0);
	printf("Client receive from server: %s\n", buf);

	close(sockfd);

	return 0;
}
