#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;

	pid = fork(); // 父进程返回子进程的id号，子进程返回值为零

	if(pid > 0) // 父进程
	{
		sleep(5);
		kill(pid, SIGKILL); // 父进程杀死子进程
		// 在Linux系统中使用命令kill -l，可查看系统支持的所有信号(共64种)
		// 在Linux系统Terminal中使用命令Ctrl + C，可向父进程发送SIGINT信号，注意是父进程，对于子进程无效
		// 要结束子进程，需要知道子进程的id号，结合kill命令使用，例如：kill id号
	}
	else if(pid == 0) // 子进程
	{
		int i = 0;
		printf("Child process id = %d\n", getpid());
		while(1)
		{
			printf("Count to %d\n", ++i);
			sleep(1);
		}
	}
	else
		perror("fork");

	return 0;
}
