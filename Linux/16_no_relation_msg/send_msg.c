#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MY_TYPE  9527
#define MY_KEY	 1314

int main(void)
{
	int msgid;

	struct msgbuf
	{
		long mtype;
		char mtext[100];
		int mnumber;
	};

	struct msgbuf buff;

	msgid = msgget(MY_KEY, IPC_CREAT); // ftok()函数生成的key一定和这里的key一致，才能表示同一个消息队列

	buff.mtype = MY_TYPE;
	printf("Please enter a string you want to send:\n");
	gets(buff.mtext);
	printf("Please enter a number you want to send:\n");
	scanf("%d", &buff.mnumber);

	msgsnd(msgid, &buff, sizeof(buff) - sizeof(buff.mtype), 0);

	return 0;
}
