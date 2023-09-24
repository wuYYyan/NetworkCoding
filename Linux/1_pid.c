#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;

	while(1)
	{
		printf("pid = %d\n", getpid()); //返回当前调用进程的进程id号
		printf("ppid = %d\n", getppid()); //返回当前调用进程的父进程id号
		printf("Hello world\n");
		sleep(1);
	}

	return 0;
}
