#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
    message connection, movement, m_recieved;
    struct sockaddr_un client_addr, server_addr;
    int ch, n = 0;
    socklen_t server_addr_size = sizeof(struct sockaddr_un);

    //TODO_4
    // create and open the FIFO for writing
    int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock_fd == -1)
    {
        perror("socket: ");
        exit(-1);
    }

    client_addr.sun_family = AF_UNIX;
    sprintf(client_addr.sun_path, "%s_%d", SOCK_ADDRESS, getpid());
    unlink(client_addr.sun_path);
    int err = bind(sock_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (err == -1)
    {
        perror("bind");
        exit(-1);
    }
    printf("Socket created \nReady to send\nReady to recieve\n");

    //TODO_5
    // read the character from the user
    char readch;
    do
    {
        printf("what is your character?: ");
        readch = getchar();
    } while (!isalpha(readch));

    // TODO_6
    // send connection message
    connection.ch = readch;
    connection.msg_type = 0;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCK_ADDRESS);
    sendto(sock_fd, &connection, sizeof(connection), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    initscr();            /* Start curses mode 		*/
    cbreak();             /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */

    movement.msg_type = 1;
    movement.ch = connection.ch;

    do
    {
        ch = getch();
        n++;
        switch (ch)
        {
        case KEY_LEFT:
            clear();
            mvprintw(0, 0, "%d Left arrow is pressed\0", n);
            movement.direction = LEFT; //TODO_9// prepare the movement message
            break;
        case KEY_RIGHT:
            clear();
            mvprintw(0, 0, "%d Right arrow is pressed\0", n);
            movement.direction = RIGHT; //TODO_9// prepare the movement message
            break;
        case KEY_DOWN:
            clear();
            mvprintw(0, 0, "%d Down arrow is pressed\0", n);
            movement.direction = DOWN; //TODO_9// prepare the movement message
            break;
        case KEY_UP:
            clear();
            mvprintw(0, 0, "%d Up arrow is pressed\0", n);
            movement.direction = UP; //TODO_9// prepare the movement message
            break;
        default:
            ch = 'x';
            break;
        }
        refresh(); /* Print it on to the real screen */

        //TODO_10
        //send the movement message
        if (ch != 'x')
            sendto(sock_fd, &movement, sizeof(movement), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        recvfrom(sock_fd, &m_recieved, sizeof(m_recieved), 0, (struct sockaddr *)&server_addr, &server_addr_size);
        if (m_recieved.msg_type == 1)
            flash();

    } while (ch != 27);

    endwin(); /* End curses mode		  */
    close(sock_fd);
    return 0;
}