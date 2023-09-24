#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

//使用命名信号量在无亲缘关系的进程之间进行通信
int main(void)
{
	sem_t *sem;
	int i = 0;

	sem = sem_open("NAMED_SEM", O_CREAT, 666, 0);
	//该信号量已被创建，因此该语句的作用只是打开信号量，后两个实参将被忽略

	while(1)
	{
		printf("Process 2: i = %d\n", i++);
		sleep(1);
		sem_post(sem);
	}

	sem_close(sem);
	//sem_unlink("NAMED_SEM"); //删除信号量

	return 0;
}
