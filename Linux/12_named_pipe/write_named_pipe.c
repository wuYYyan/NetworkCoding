#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

//打开有名管道(先入先出文件)，向管道中写入数据，因此需要给main函数传递参数
int main(int argc, char *argv[])
{
	int fd;
	char buf[100];

	fd = open("my_fifo", O_WRONLY);
	if(fd == -1)
		perror("open");

	if(argc == 1)
	{
		printf("Please send something to the named pipe:\n");
		exit(EXIT_FAILURE);
	}

	strcpy(buf, argv[1]); //argv[0]是程序名，argv[1]才是想要写入的内容
	write(fd, buf, sizeof(buf));
	printf("Write to the pipe: %s\n", buf);

	return 0;
}
