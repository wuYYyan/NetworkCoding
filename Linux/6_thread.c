#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_function(void *arg);

int main(void)
{
	pthread_t pthread;
	int ret;
	int count = 8;

	//在pthread_create函数中，最后一个形参的类型是void *，所以在调用时，需要强制类型转换
	ret = pthread_create(&pthread, NULL, thread_function, &count);
	//线程所占用的所有资源都依赖于进程，当进程结束时，线程也会结束
	if(ret != 0)
	{
		perror("pthread_create");
		exit(1);
	}

	//while(1);
	pthread_join(pthread, NULL);
	printf("The thread is over, process is over too.\n");

	return 0;
}

void *thread_function(void *arg)
{
	int i;
	printf("Thread begins running\n");

	//对arg先进行强制类型转换，将void *转换为int *，再取内容
	for(i = 0; i < *(int *)arg; i++)
	{
		printf("Hello world\n");
		sleep(1);
	}
	return NULL;
}
