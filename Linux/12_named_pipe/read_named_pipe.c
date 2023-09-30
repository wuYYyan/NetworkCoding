#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int ret;
	int fd; // 文件描述符的类型是整型
	char buf[100];

	ret = mkfifo("my_fifo", 666); // 在此程序所在的路径下，对创建的有名管道拥有读写权限
	// 当本程序运行之后，在Linux系统下使用ls命令可以看到my_fifo文件
	if(ret != 0)
		perror("mkfifo");

	printf("Prepare reading from named pipe:\n");

	// 像操作文件一样操作有名管道
	fd = open("my_fifo", O_RDWR);
	if(fd == -1)
		perror("open");

	while(1)
	{
		memset(buf, '\0', sizeof(buf)); // 按字节对buf进行初始化
		read(fd, buf, sizeof(buf)); // 当没有进程向管道中写内容时，read函数会阻塞
		printf("Read from named pipe: %s\n", buf);
		sleep(1);
	}

	return 0;
}
