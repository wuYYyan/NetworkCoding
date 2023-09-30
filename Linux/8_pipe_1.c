/*
	parent process: write pipe(理解为自来水公司一端)
	child  process: read  pipe(理解为用户一端)
*/
//任务间通信：管道/无名管道，无名管道是单向流通的
//管道是双端口的，既可以写入也可以读出
//有名管道：先入先出的文件
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void)
{
	int fd[2]; //two file descriptors(两个文件描述符，fd[0]为读端，fd[1]为写端)
	int pid;
	
	// 函数pipe()用于创建一个管道，其参数为返回参数，即在调用函数之前不需要提前设置参数
	// fd[0]为读端，fd[1]为写端 
	if(pipe(fd) == -1)
		perror("pipe");

	pid = fork(); //复制一份父进程(含管道)创建子进程，只需更改管道读写权限即可
	if(pid > 0)  //parent process，返回子进程的id号
	{
		//把管道当做文件来处理，使用close、write、read等函数
		close(fd[0]); // 关闭读端
		sleep(5);
		write(fd[1], "ab", 2);

		while(1);
	}
	else if(pid == 0) //child process，返回0
	{
		char ch[2]; // 读取处的内容存放到ch中

		printf("Child process is waiting for data: \n");
		close(fd[1]); // 关闭写端
		read(fd[0], ch, 2);
		printf("Read from pipe: %s\n", ch);
	}

	return 0;
}
