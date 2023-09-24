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

	if(pid == 0)  //child process: write to the pipe(子进程向父进程中写入内容)
	{
		char ch = '*';
		int n = 0;

		close(fd[0]);

		while(1)
		{
			write(fd[1], &ch, 1);
			printf("count = %d\n", ++n);
			//管道的默认容量为65536字节，当写入的数据超过65536字节时，会阻塞
		}
	}
	else if(pid > 0)  //parent process: wait until child process is over(父进程等待子进程结束)
	{
		waitpid(pid, NULL, 0);
	}
}
