#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "data_struct.h"
int main()
{

	int fd, fd2, n, i;
	char str[100];

	while ((fd = open("/tmp/fifo_teste", O_WRONLY)) == -1)
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
	printf("client fifo just opened for writing\n");

	while ((fd2 = open("/tmp/fifo_teste2", O_RDONLY)) == -1)
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
	printf("fifo2 just opened\n");

	while (1)
	{
		message_type message;
		// manda string do nome da funcao
		printf("Insira a função que pretende correr: \n\nf1\tou\tf2\tou\tf3\n");
		do
		{
			fgets(message.f_name, 100, stdin);
			message.f_name[strlen(message.f_name) - 1] = '\0';
		} while (strcmp(message.f_name, "f1") && strcmp(message.f_name, "f2") && strcmp(message.f_name, "f3"));

		if (!strcmp(message.f_name, "f3"))
		{
			message.funct_type = 0;
			printf("Insira um argumento inteiro:\n");
			fgets(str, 100, stdin);
			sscanf(str, "%d", &n);
			message.arg = n;
		}else
		{
			message.funct_type = 1;
			message.arg = 0;
		}
		write(fd, &message, sizeof(message));

		// recebe o nome da funcao, executa e dá print
		// n é str da func
		n = read(fd2, &i, 100);
		if (n <= 0)
		{
			perror("read ");
			exit(-1);
		}
		printf("RESPOSTA:\n\t%d\n\n", i);
		
	}
}
