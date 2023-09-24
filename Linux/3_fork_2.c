#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int count = 0;

int main(void)
{
	pid_t pid;
//	int count = 0;

	pid = fork();

	//微观上：先调用父进程，再调用子进程
	//宏观上：父进程与子进程同时执行，时间上的性能差异可以忽略不计
	if(pid > 0)  //parent process
	{
		while(1)
		{
			printf("Hello world, count = %d\n", count++);
			//父子进程具有相互独立的内存空间，count变量在父子进程中互不影响
			sleep(1);
		}
	}
	else if(pid == 0)  //child process
	{
		while(1)
		{
			printf("Good morning, count = %d\n", count++);
			sleep(2);
		}
	}
	else
		perror("fork");

	return 0;
}
