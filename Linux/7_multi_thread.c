#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread1_function(void *arg);
void *thread2_function(void *arg);

int count = 0; //线程共享进程的资源，与4_fork_3.c相区别(各个进程之间互不影响)

int main(void)
{
	pthread_t pthread1, pthread2; //创建线程类型的变量
	int ret;

	//创建第一个线程
	ret = pthread_create(&pthread1, NULL, thread1_function, NULL);
	if(ret != 0)
	{
		perror("pthread_create");
		exit(1);
	}

	//创建第二个线程
	ret = pthread_create(&pthread2, NULL, thread2_function, NULL);
	if(ret != 0)
	{
		perror("pthread_create");
		exit(1);
	}

	pthread_join(pthread1, NULL); //进程等待第一个线程结束
	pthread_join(pthread2, NULL); //进程等待第二个线程结束
	printf("The thread is over, process is over too.\n");

	return 0;
}

// 两个线程输出的count成对增加，因为它们共享系统资源
void *thread1_function(void *arg)
{
	printf("Thread1 begins running\n");

	while(1)
	{
		printf("Thread1 count = %d\n", count++);
		sleep(1);
	}

	return NULL;
}

void *thread2_function(void *arg)
{
	printf("Thread2 begins running\n");

	while(1)
	{
		printf("Thread2 count = %d\n", count++);
		sleep(1);
	}

	return NULL;
}
