#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MY_TYPE  9527

int main(void)
{
	int msgid;
	pid_t pid;

	//使用结构体定义消息队列类型，可以发送多种数据类型
	struct msgbuf
	{
		long mtype; //消息类型，必须大于零
		char mtext[100]; //消息内容：字符数组
		int number; //消息内容：整型变量
		//还可以定义其他类型的变量
	};

	struct msgbuf buff; //创建结构体对象

	msgid = msgget(IPC_PRIVATE, IPC_CREAT); 
	//创建消息队列，返回消息队列的标识符(在kernel中对内存的索引/键)

	pid = fork(); //父子进程的buff相互独立，但是消息队列是共享的

	if(pid > 0) //父进程
	{
		sleep(5);

		buff.mtype = MY_TYPE;
		printf("Please enter a string you want to send:\n");
		gets(buff.mtext); //mtext是指针，不需要取地址符
		printf("Please enter a number you want to send:\n");
		scanf("%d", &buff.number);

		msgsnd(msgid, &buff, sizeof(buff) - sizeof(buff.mtype), 0); //将buff中的内容写入消息队列并发送
		//注意消息的大小并不是整个结构体的大小，要除去消息类型

		waitpid(pid, NULL, 0); //父进程等待子进程结束后再结束
	}
	else if(pid == 0) //子进程
	{
		printf("Child process is waiting for msg:\n");
		msgrcv(msgid, &buff, sizeof(buff) - sizeof(buff.mtype), MY_TYPE, 0); 
		//从消息队列中读取的内容存入子进程的buff中(父子进程的buff相互独立)
		//接受的消息类型与发送的消息类型必须一致，否则接受不到消息

		printf("Child process read from msg: %s, %d\n", buff.mtext, buff.number);
		msgctl(msgid, IPC_RMID, NULL);
	}
	else
		perror("fork");

	return 0;
}
