#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

void *thread1_function(void *arg);
void *thread2_function(void *arg);

pthread_mutex_t mutex; //定义互斥锁

int main(void)
{
	pthread_t pthread1, pthread2;
	int ret;

	pthread_mutex_init(&mutex, NULL);

	ret = pthread_create(&pthread1, NULL, thread1_function, NULL);
	if(ret != 0)
	{
		perror("pthread_create");
		exit(1);
	}

	ret = pthread_create(&pthread2, NULL, thread2_function, NULL);
	if(ret != 0)
	{
		perror("pthread_create");
		exit(1);
	}

	pthread_join(pthread1, NULL); //等待第一个线程结束
	pthread_join(pthread2, NULL); //等待第二个线程结束
	printf("The thread is over, process is over too.\n");

	return 0;
}

void *thread1_function(void *arg)
{
	int i;

	while(1)
	{
		pthread_mutex_lock(&mutex); //加锁
		for(i = 0; i < 10; i++)
		{
			printf("Hello world\n");
			sleep(1);
		}
		pthread_mutex_unlock(&mutex); //解锁
		sleep(1);
	}
	return NULL;
}

void *thread2_function(void *arg)
{
	int i;
	sleep(1);

	while(1)
	{
		pthread_mutex_lock(&mutex); //加锁，若失败则阻塞
		for(i = 0; i < 10; i++)
		{
			printf("Good morning\n");
			sleep(1);
		}
		pthread_mutex_unlock(&mutex); //解锁
		sleep(1);
	}
	return NULL;
}
