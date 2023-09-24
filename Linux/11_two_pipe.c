//管道都是单向通信的，要实现父子进程之间的交互就需要两条管道，父子进程各一条
//无名管道只适用于具有公共祖先(亲缘关系)的进程之间的通信，因此，无名管道不能用于网络通信
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
	pid_t pid;
	int fd[2]; //父进程管道
	int fd2[2]; //子进程管道

	if(pipe(fd) == -1)
		perror("pipe");
	if(pipe(fd2) == -1)
		perror("pipe");

	pid = fork();

	if(pid == 0) //子进程将从父进程中读取的内容转换为大写后写入管道
	{
		char tmp[100];
		int i;

		close(fd[1]); //子进程从父进程的管道读取，因此对于子进程来说关闭写端
		close(fd2[0]); //向父进程传输，因此保留自己管道的写端，关闭读端

		while(1)
		{
			memset(tmp, '\0', sizeof(tmp)); //清空tmp
			read(fd[0], tmp, sizeof(tmp));

			for(i = 0; i < sizeof(tmp); i++)
				tmp[i] = toupper(tmp[i]);

			write(fd2[1], tmp, sizeof(tmp));
		}
	}
	else if(pid > 0) //父进程从键盘读取内容并写入管道，然后从管道读取子进程写入的内容并打印
	{
		char tmp[100];
		close(fd[0]); //向子进程传输，因此保留自己管道的写端，关闭读端
		close(fd2[1]); //父进程从子进程的管道读取，因此对于父进程来说关闭写端

		while(1)
		{
			memset(tmp, '\0', sizeof(tmp));
			gets(tmp); //整行读取
			write(fd[1], tmp, sizeof(tmp));

			memset(tmp, '\0', sizeof(tmp));
			read(fd2[0], tmp, sizeof(tmp));
			printf("After change: %s\n", tmp);
		}
	}

	return 0;
}
