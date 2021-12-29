
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#define WINDOW_SIZE 15

direction_t random_direction()
{
    return random() % 4;
}


void new_position(int *x, int *y, direction_t direction)
{
    switch (direction)
    {
    case UP:
        (*x)--;
        if (*x == 0)
            *x = 2;
        break;
    case DOWN:
        (*x)++;
        if (*x == WINDOW_SIZE - 1)
            *x = WINDOW_SIZE - 3;
        break;
    case LEFT:
        (*y)--;
        if (*y == 0)
            *y = 2;
        break;
    case RIGHT:
        (*y)++;
        if (*y == WINDOW_SIZE - 1)
            *y = WINDOW_SIZE - 3;
        break;
    default:
        break;
    }
}

int find_char (clients client[] ,int check_char , int n_chars){
   int i =-1;
    do {++i;
        if (i> n_chars ) return -1;
    }while (check_char != client[i].ch);
    return i;
}

int main()
{
    int n_chars = 0;

    // TODO_3
    // CREATE SOCKET
    int sock_fd;
	sock_fd= socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sock_fd == -1){
		perror("socket: ");
		exit(-1);
	}

	struct sockaddr_un local_addr;
	local_addr.sun_family = AF_UNIX;
	strcpy(local_addr.sun_path, SOCK_ADDRESS);

	unlink(SOCK_ADDRESS);
	int err = bind(sock_fd, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if(err == -1) {
        perror("bind");
        exit(-1);
    }

    // ncurses initialization
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    /* creates a window and draws a border */
    WINDOW *my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0, 0);
    wrefresh(my_win);
    
    /* information about the character */
    message m_recieved, reply_message;
    clients client[100];
    //char buffer[100];
    struct sockaddr_un client_addr;
	socklen_t client_addr_size = sizeof(struct sockaddr_un);
    int n_client, nbytes;
    while (1)
    {   
        // TODO_7
        // receive message from the clients
        nbytes = recvfrom(sock_fd, &m_recieved, sizeof(m_recieved), 0,( struct sockaddr *)&client_addr, &client_addr_size);
		if (nbytes <= 0)
		{
			perror("read");
			exit(-1);
		}
        
        //TODO_8
        // process connection messages
        int i = 0;
        if (m_recieved.msg_type == 0){
            
            do{
                if (m_recieved.ch == client[i].ch) printf("CARATER JA EM USO ERRO!"); 
                i++;
            }while  (i< n_chars);
            n_client = n_chars;
            client[n_chars].x = WINDOW_SIZE/2;
            client[n_chars].y = WINDOW_SIZE/2;
            client[n_chars].ch = m_recieved.ch;
            n_chars ++;
            
            //escreve o carater na posição pré-definida
        }
        
        // TODO_11
        // process the movement message
        else{ //(m_recieved.msg_type == 1 )
            // recebe a direction e faz deslocação nesse sentido( usar função acima)
            n_client = find_char(client, m_recieved.ch, n_chars); //função que vai encontrar a posição de memória que pretendemos para este carater
            wmove(my_win, client[n_client].x, client[n_client].y);
            waddch(my_win,' ');
            new_position(&client[n_client].x, &client[n_client].y, m_recieved.direction);
        }

        /* draw mark on new position */
        
        wmove(my_win, client[n_client].x, client[n_client].y);
        waddch(my_win, client[n_client].ch | A_BOLD);
        wrefresh(my_win);
    }

    nbytes = sendto(sock_fd, &reply_message, sizeof(reply_message), 0,(const struct sockaddr *) &client_addr, client_addr_size);
    endwin(); /* End curses mode		  */
    close(sock_fd);
    return 0;
}