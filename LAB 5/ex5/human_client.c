#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>


int main()
{
    //TODO_4
    int SIZE = 50;
    char adress_keyboard[SIZE];
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1){
        perror("socket: ");
        exit(-1);
    } 
    printf("IP do servidor? \n");
    fgets(adress_keyboard, SIZE , stdin);// gets adress from user
    adress_keyboard[strlen(adress_keyboard)-1] = '\0';
    

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SOCK_PORT);
    if( inet_pton(AF_INET, adress_keyboard, &server_addr.sin_addr) < 1){
		printf("no valid address: \n");
		exit(-1);
	}
    
    


    //TODO_5
    // read the character from the user
    char ch;
    do{
        printf("what is your character(a..z)?: ");
        ch = getchar();
        ch = tolower(ch);  
    }while(!isalpha(ch));


    // TODO_6
    // send connection message
    remote_char_t m, m_receive;
    m.msg_type = 0;
    m.ch = ch;
   sendto(sock_fd, &m, sizeof(remote_char_t), 0, 
            (const struct sockaddr *)&server_addr, sizeof(server_addr));
    

	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    int n = 0;

    //TODO_9
    // prepare the movement message
    m.msg_type = 1;
    m.ch = ch;
    
    int key;
    do
    {
    	key = getch();		
        n++;
        switch (key)
        {
        case KEY_LEFT:
            mvprintw(0,0,"%d Left arrow is pressed", n);
            //TODO_9
            // prepare the movement message
           m.direction = LEFT;
            break;
        case KEY_RIGHT:
            mvprintw(0,0,"%d Right arrow is pressed", n);
            //TODO_9
            // prepare the movement message
            m.direction = RIGHT;
            break;
        case KEY_DOWN:
            mvprintw(0,0,"%d Down arrow is pressed", n);
            //TODO_9
            // prepare the movement message
           m.direction = DOWN;
            break;
        case KEY_UP:
            mvprintw(0,0,"%d :Up arrow is pressed", n);
            //TODO_9
            // prepare the movement message
            m.direction = UP;
            break;

        default:
            key = 'x';
            break;
        }

        //TODO_10
        //send the movement message
         if (key != 'x'){
           sendto(sock_fd, &m, sizeof(remote_char_t), 0, 
                (const struct sockaddr *)&server_addr, sizeof(server_addr));
           recv(sock_fd, &m_receive, sizeof(remote_char_t), 0);
           if(m_receive.msg_type==3){
               flash();
           }
    
        }
        refresh();			/* Print it on to the real screen */
    }while(key != 27);
    
    
  	endwin();			/* End curses mode		  */

	return 0;
}