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
    int sleep_delay;
    direction_t direction;
    int n = 0;
    message connection, movement;
    //TODO_4

    int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock_fd == -1)
    {
        perror("socket: ");
        exit(-1);
    }
    printf(" socket created \n Ready to send\n");

    //TODO_5
    // machine will generate a random character and send to the server making the connection
    connection.ch = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[random() % 52];
    connection.msg_type = 0;
    movement.ch = connection.ch;

    struct sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCK_ADDRESS);
    sendto(sock_fd, &connection, sizeof(connection), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // TODO_6
    movement.msg_type = 1;

    while (1)
    {
        sleep_delay = random() % 700000;
        usleep(sleep_delay);
        direction = random() % 4;
        n++;

        switch (direction)
        {
        case LEFT:
            printf("%d Going Left   ", n);
            movement.direction = LEFT;
            break;
        case RIGHT:
            printf("%d Going Right   ", n);
            movement.direction = RIGHT;
            break;
        case DOWN:
            printf("%d Going Down   ", n);
            movement.direction = DOWN;
            break;
        case UP:
            printf("%d Going Up    ", n);
            movement.direction = UP;
            break;
        }
        //TODO_9
        // movement is adding the arrow typed to the movement.ch

        //TODO_10
        sendto(sock_fd, &movement, sizeof(movement), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    return 0;
}