#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MY_TYPE  9527 // 消息类型，必须大于零
#define MY_KEY	 1314 // 消息队列的key

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

	msgid = msgget(MY_KEY, IPC_CREAT); // 一定和发送端的key一致，才能表示同一个消息队列
	// 如果仍然使用IPC_PRIVATE，那么每次运行都会创建一个新的消息队列，而不是使用已有的消息队列

	while(1) // 死循环一直等待接收消息
	{
		printf("Process is waiting for msg:\n");
		msgrcv(msgid, &buff, sizeof(buff) - sizeof(buff.mtype), MY_TYPE, 0);
		printf("Process read from msg: %s, %d\n", buff.mtext, buff.mnumber);
	}
	msgctl(msgid, IPC_RMID, NULL); // 删除消息队列

	return 0;
}
