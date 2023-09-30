#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MY_KEY	9527 //必须与write_shm.c中的MY_KEY相同

int main(void)
{
	int shmid;

	shmid = shmget(MY_KEY, 1024, IPC_CREAT); 
	// 指定编号的共享内存已经存在，所以这条语句的作用就是打开共享内存

	char *c_addr;
	c_addr = shmat(shmid, NULL, 0); //建立映射关系

	printf("Read from shared memory: %s\n", c_addr);
	shmdt(c_addr); //解除映射关系

	return 0;
}
