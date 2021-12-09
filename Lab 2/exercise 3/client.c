#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){


	int fd;
	char str[100];
	
	while((fd = open("/tmp/fifo_teste", O_WRONLY))== -1){
	  if(mkfifo("/tmp/fifo_teste", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("client fifo just opened for writing\n");


	while(1){

		// manda string do nome da funcao 
		printf("f1() ou f2()\n");
		do 
		{
			fgets(str, 100, stdin);
			str[strlen(str)-1]= '\0';
		} while (strcmp(str, "f1") && strcmp(str, "f2"));
	  
		
		write(fd, str, 100);

	}

}
