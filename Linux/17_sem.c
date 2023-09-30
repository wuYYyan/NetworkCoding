// 编译时要添加选项 -pthread
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

// 子进程控制父进程的执行
int main(void)
{
	sem_t *sem_id = NULL; //信号量的指针
	pid_t pid;

	/*
	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
	系统调用在调用进程的虚拟地址空间中创建一个新映射，映射的起始地址由addr指定，映射的长度由length指定
	创建成功时会返回映射成功的新地址，失败时会返回MAP_FAILED
	*/

	sem_id = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	// 将信号量放到共享内存区域中，确保父子进程中用到的信号量是同一个信号量

	sem_init(sem_id, 1, 0); // 创建在父子进程之间共享的信号量，且资源的初始计数为0
	// 第二个参数pshared为0表示信号量在调用进程中的线程间共享，非0表示信号量在进程间共享(共享内存区域)
	// 即信号量既可以在进程间共享，又可以在线程间共享

	pid = fork();

	//子进程通过信号量控制父进程的执行
	if(pid > 0) //父进程
	{
		while(1)
		{
			sem_wait(sem_id); 
			// 检查信号量是否大于零，如果大于零，可以继续执行并将信号量减一；如果小于等于零，就阻塞等待
			printf("This is parent process.\n");
			sleep(1);
		}
	}
	else if(pid == 0) //子进程
	{
		while(1)
		{
			printf("This is child process.\n");
			sleep(5);
			sem_post(sem_id); // 发布信号量，即将信号量的资源计数加一
		}
	}
	else
		perror("fork");

	return 0;
}
