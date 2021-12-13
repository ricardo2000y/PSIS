
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
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

int main()
{

    int fd;
    // TODO_3
    // create and open the FIFO for reading
    while ((fd = open(fifo_loc, O_RDONLY)) == -1)
    {
        if (mkfifo(fifo_loc, 0666) != 0)
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
    int ch;
    int pos_x;
    int pos_y;
    int n;
    direction_t direction;
    message m_recieved;
    while (1)
    {   
        // TODO_7
        // receive message from the clients
        n = read(fd, &m_recieved, sizeof(m_recieved));
		if (n <= 0)
		{
			perror("read ");
			exit(-1);
		}

        //TODO_8
        // process connection messages
        if (m_recieved.msg_type == 0){

            //escreve o caratér numa posição random (usar função acima)
        }

        // TODO_11
        // process the movement message
        else{ //(m_recieved.msg_type == 1 )
            // recebe a seta e faz deslocação nesse sentido( usar função acima)
        }

        /* draw mark on new position */
        wmove(my_win, pos_x, pos_y);
        waddch(my_win, ch | A_BOLD);
        wrefresh(my_win);
    }
    endwin(); /* End curses mode		  */

    return 0;
}