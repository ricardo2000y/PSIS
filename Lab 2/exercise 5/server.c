#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "funcs.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "data_struct.h"

int main()
{

	int fd, fd2, k;

	while ((fd = open("/tmp/fifo_teste", O_RDONLY)) == -1)
	{
		if (mkfifo("/tmp/fifo_teste", 0666) != 0)
		{
			printf("problem creating the fifo\n");
			exit(-1);
		}
		else
		{
			printf("fifo created\n");
		}
	}
	printf("fifo just opened\n");

	while ((fd2 = open("/tmp/fifo_teste2", O_WRONLY)) == -1)
	{
		if (mkfifo("/tmp/fifo_teste2", 0666) != 0)
		{
			printf("problem creating the fifo\n");
			exit(-1);
		}
		else
		{
			printf("fifo2 created\n");
		}
	}
	printf("server fifo just opened for writing\n");

	int n;
	char str[100];
	while (1)
	{
		// recebe o nome da funcao, executa e dá print
		// n é str da func
		message_type message;
		n = read(fd, &message, sizeof(message));
		if (n <= 0)
		{
			perror("read ");
			exit(-1);
		}
		printf("%s\n", message.f_name);
		strcpy(str, message.f_name);
		if (!strcmp(str, "f1"))
		{
			k = f1();
			write(fd2, &k, 100);
		}
		else if (!strcmp(str, "f2"))
		{
			k = f2();
			write(fd2, &k, 100);
		}
		else
		{
			k = f3(message.arg);
			write(fd2, &k, 100);
		}

		//printf("mandei info\n");
	}
}