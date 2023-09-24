#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char msg[] = "Hello world";

#define MY_KEY	9527

int main(void)
{
	int shmid;

	shmid = shmget(MY_KEY, 1024, IPC_CREAT);

	char *p_addr;
	p_addr = shmat(shmid, NULL, 0);

	memset(p_addr, '\0', sizeof(msg));
	memcpy(p_addr, msg, sizeof(msg));

	shmdt(p_addr);

//	shmctl(shmid, IPC_RMID, NULL); //删除共享内存

	return 0;
}
