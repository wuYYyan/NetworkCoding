#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

void *thread1_function(void *arg);
void *thread2_function(void *arg);

int count = 0;
sem_t sem; //定义信号量，在两个线程之间完全可见。因此不需要使用mmap()函数将信号量放到共享内存区域中

int main(void)
{
	pthread_t pthread1, pthread2;
	int ret;

	sem_init(&sem, 0, 0); //创建用于线程之间(pshared = 0)通讯的信号量
	//因为线程之间共享资源，所以不需要将信号量放到共享内存区域中

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

	pthread_join(pthread1, NULL);
	pthread_join(pthread2, NULL);
	printf("The thread is over, process is over too.\n");

	return 0;
}

void *thread1_function(void *arg)
{
	while(1)
	{
		sem_wait(&sem); //等待信号量，如果信号量为0，则阻塞。注意实参要传递地址
		printf("Thread1 count = %d\n", count++);
	}
	return NULL;
}

void *thread2_function(void *arg)
{
	while(1)
	{
		printf("Thread2 is running!\n");
		sleep(5);
		sem_post(&sem); //发布信号量，即将信号量加一。注意实参要传递地址
	}
	return NULL;
}
