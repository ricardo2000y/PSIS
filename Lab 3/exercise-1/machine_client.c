#include "remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main()
{
    int sleep_delay;
    direction_t direction;
    int n = 0;
    message connection,movement;
    //TODO_4

    int fd;
    while ((fd = open(fifo_loc, O_WRONLY)) == -1)
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

    //TODO_5
    // machine will generate a random character and send to the server making the connection
    connection.ch = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[random() % 52];
    write(fd, &connection, sizeof(connection));

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
            break;
        case RIGHT:
            printf("%d Going Right   ", n);
            break;
        case DOWN:
            printf("%d Going Down   ", n);
            break;
        case UP:
            printf("%d Going Up    ", n);
            break;
        }
        //TODO_9
        // movement is adding the arrow typed to the movement.ch
        //TODO_10
    }

    return 0;
}