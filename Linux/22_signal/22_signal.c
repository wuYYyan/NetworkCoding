#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void function(int signo); // 信号处理函数有固定的格式
// void (*sighandler)(int signo);

int main(void)
{
	int i = 0;

	printf("pid = %d\n", getpid());

	// 根据不同的信号，执行不同的信号处理函数
	signal(SIGINT, function); // 重新定义了SIGINT信号的处理函数, SIGINT由ctrl+c触发
	signal(SIGQUIT, function);
	// SIGKILL/SIGQUIT信号不能被捕获/修改，所以对SIGKILL/SIGQUIT调用signal函数调用无效

	while(1)
	{
		printf("Count to %d\n", ++i);
		sleep(1);
	}

	return 0;
}

void function(int signo)
{
	if(signo == SIGINT)
	{
		printf("You have just triggered a ctrl+c operation.\n");
		exit(1); // 必须添加退出语句，否则程序会一直执行
	}
	else if(signo == SIGQUIT)
		printf("Trig a SIGQUIT signal.\n");
}
