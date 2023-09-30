#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid; // pid_t是进程标识符类型，定义在sys/types.h中

	while (1)
	{
		printf("pid = %d\n", getpid()); //返回当前调用进程的进程id号
		printf("ppid = %d\n", getppid()); //返回当前调用进程的父进程id号
		printf("Hello world\n");
		sleep(1);
	}
	// Linux命令：pstree -p，可以查看进程树，现在大多数Linux发行版都以systemd作为init进程，其pid号为1

	return 0;
}
