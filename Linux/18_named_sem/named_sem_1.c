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
	//初始化并打开一个命名信号量，靠标识信号量的字符串进行区分
	//666是确定信号量的权限，也就是所有用户都有读写权限(一共有三种权限：可读可写可执行)

	while(1)
	{
		sem_wait(sem); //等待or检查信号量
		printf("Process 1: i = %d\n", i++);
	}

	sem_close(sem);
	//sem_unlink("NAMED_SEM"); //删除信号量

	return 0;
}
