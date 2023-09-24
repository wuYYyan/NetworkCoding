//无名管道练习
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int fd[2];

	if(pipe(fd) == -1)
		perror("pipe");

	pid = fork();

	if(pid == 0) //子进程将从键盘读入的内容写入管道
	{
		char tmp[100];

		close(fd[0]);

		while(1)
		{
			scanf("%s", tmp);
			write(fd[1], tmp, sizeof(tmp));
		}
	}
	else if(pid > 0) //父进程从管道中读取子进程写入的内容并保存到tmp中
	{
		char tmp[100];
		close(fd[1]);

		while(1)
		{
			printf("Parent process is waiting for the data from pipe:\n");
			read(fd[0], tmp, sizeof(tmp));
			printf("read from pipe: %s\n", tmp);
		}
	}

	return 0;
}
