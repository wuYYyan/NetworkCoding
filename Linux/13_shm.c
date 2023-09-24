#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char msg[] = "Hello world";

//在父子进程之间使用共享内存(shm = shared memory)进行通讯
int main(void)
{
	int shmid;
	pid_t pid;

	shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT); 
	//创建共享内存，返回共享内存的标识符(在kernel中对内存的索引/键)

	pid = fork(); //创建子进程

	if(pid > 0) //父进程
	{
		char *p_addr;
		p_addr = shmat(shmid, NULL, 0); 
		//将共享内存映射到父进程的地址空间，父进程对该共享内存具有读写权限，返回映射之后的内存单元的地址

		memset(p_addr, '\0', sizeof(msg)); //按字节清空
		memcpy(p_addr, msg, sizeof(msg)); //按字节拷贝

		shmdt(p_addr); //为父进程解除映射关系

		waitpid(pid, NULL, 0); //父进程等待子进程结束后再结束
	}
	else if(pid == 0) //子进程
	{
		char *c_addr;
		c_addr = shmat(shmid, NULL, 0); 
		//将共享内存映射到子进程的地址空间，子进程对该共享内存具有读写权限，返回映射之后的内存单元的地址

		printf("Child process waits a short time: \n");
		sleep(3);
		printf("Child process reads from shared memory: %s\n", c_addr);
		shmdt(c_addr); //为子进程解除映射关系
	}
	else
		perror("fork");

	return 0;
}
