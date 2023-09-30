#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// compile and link with -pthread
void *thread_function(void *arg);

int main(void)
{
	pthread_t pthread; // 创建线程id号类型的变量
	int ret;
	int count = 8;

 	// man pthread_create：查看函数的具体使用方法，作用是用于进程创建线程
	// 线程创建成功时，返回0；失败时，返回错误码
	// 由于函数名就是函数在内存中的首地址，因此可以直接把函数名作为第三个参数使用
	// 在pthread_create函数中，最后一个形参的类型是void *，所以在调用时，需要强制类型转换
	ret = pthread_create(&pthread, NULL, thread_function, &count);
	//线程所占用的所有资源都依赖于进程，当进程结束时，线程也会结束，所以后面必须join
	if(ret != 0)
	{
		perror("pthread_create");
		exit(1); //创建线程失败，退出进程
	}

	//while(1);
	pthread_join(pthread, NULL); //进程等待线程结束后再结束
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
