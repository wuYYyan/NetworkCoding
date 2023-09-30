#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT_ID	8800
#define SIZE	100

//只改变服务器端的代码，不改变客户端的代码，就可以实现并发服务器
int main(void)
{
	int i;

	int sockfd, client_sockfd;
	struct sockaddr_in my_addr, client_addr;
	int addr_len;
	char welcome[SIZE] = "Welcome to connect to the sever!";

	// 1.socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// 2.bind()
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT_ID);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));

	// 3.listen()
	listen(sockfd, 10);

	addr_len = sizeof(struct sockaddr);

	// 预先派发16(2^4 = 16)个子进程
	for(i = 0; i < 4; i++)
		fork();

	while(1)
	{
		printf("Server is waiting for client to connect:\n");
		// 4.accept()
		client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
		printf("Client IP address = %s\n", inet_ntoa(client_addr.sin_addr));
		// 5.send()
		send(client_sockfd, welcome, SIZE, 0);
		printf("Disconnect the client request.\n");
		// 6.close()
		close(client_sockfd);
	}

	close(sockfd);

	return 0;
}
