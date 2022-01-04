
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define WINDOW_SIZE 15

// STEP 1
typedef struct ch_info_t
{
    int ch;
    int pos_x, pos_y;
} ch_info_t;

direction_t random_direction(){
    return  random()%4;

}

    void new_position(int* x, int *y, direction_t direction){
        switch (direction)
        {
        case UP:
            (*x) --;
            if(*x ==0)
                *x = 2;
            break;
        case DOWN:
            (*x) ++;
            if(*x ==WINDOW_SIZE-1)
                *x = WINDOW_SIZE-3;
            break;
        case LEFT:
            (*y) --;
            if(*y ==0)
                *y = 2;
            break;
        case RIGHT:
            (*y) ++;
            if(*y ==WINDOW_SIZE-1)
                *y = WINDOW_SIZE-3;
            break;
        default:
            break;
        }
}

int find_ch_info(ch_info_t char_data[], int n_char, int ch){
    for (int i = 0 ; i < n_char; i++){
        if(ch == char_data[i].ch){
            return i;
        }
    }
    return -1;
}

int main()
{	
    
       
    //STEP 2
    ch_info_t char_data[100];
    int n_chars = 0;


    
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1){
	    perror("socket: ");
	    exit(-1);
    }

  

    struct sockaddr_in local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(SOCK_PORT);
    local_addr.sin_addr.s_addr = INADDR_ANY; 

    bind(sock_fd, ( struct sockaddr *)&local_addr, sizeof(local_addr));
 
	initscr();		    	
	cbreak();				
    keypad(stdscr, TRUE);   
	noecho();			    

    /* creates a window and draws a border */
    WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0 , 0);	
	wrefresh(my_win);

    int ch;
    int pos_x;
    int pos_y;
    int n_bytes;
    remote_char_t m;

    direction_t  direction;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(struct sockaddr_un);

    // 6.2 Step 2 (server.c)
    struct sockaddr_in remote_display_client[10]; 
    //--//
    int client =0;
    while (1)
    {
        
        n_bytes = recvfrom(sock_fd, &m, sizeof(remote_char_t), 0, 
                        ( struct sockaddr *)&client_addr, &client_addr_size);

        // 6.2 Step 2 (server.c)
        if(m.msg_type == 5){ // msg type = 5 -> new message
            // incrementar client
            ++client;

            remote_display_client[client].sin_family=client_addr.sin_family;
            remote_display_client[client].sin_addr=client_addr.sin_addr;
            remote_display_client[client].sin_port=client_addr.sin_port;
            //remote_display_client[client].sin_zero=
            
        }
        

        if (n_bytes!= sizeof(remote_char_t)){
            continue;
        }
        if(m.msg_type == 0){
            ch = m.ch;
            pos_x = WINDOW_SIZE/2;
            pos_y = WINDOW_SIZE/2;

            //STEP 3
            char_data[n_chars].ch = ch;
            char_data[n_chars].pos_x = pos_x;
            char_data[n_chars].pos_y = pos_y;
            n_chars++;
        }
        if(m.msg_type == 1){
            //STEP 4
            int ch_pos = find_ch_info(char_data, n_chars, m.ch);
            if(ch_pos != -1){
                pos_x = char_data[ch_pos].pos_x;
                pos_y = char_data[ch_pos].pos_y;
                ch = char_data[ch_pos].ch;
                /*deletes old place */
                wmove(my_win, pos_x, pos_y);
                waddch(my_win,' ');

                /* claculates new direction */
                direction = m.direction;

                /* claculates new mark position */
                new_position(&pos_x, &pos_y, direction);
                char_data[ch_pos].pos_x = pos_x;
                char_data[ch_pos].pos_y = pos_y;

            }   
            int same = -1;  
            for(int i = 0 ; i< n_chars; i++){
                if(char_data[i].pos_x == pos_x && char_data[i].pos_x){
                    same ++;
                }
            }
            m.msg_type = 2;  
            if (same > 0){
                m.msg_type = 3;              
            } 
            char remote_addr_str[100];
		    int remote_port = ntohs(client_addr.sin_port);
		    if (inet_ntop(AF_INET, &client_addr.sin_addr, remote_addr_str, 100) == NULL){
			    perror("converting remote addr: ");
		    }
            sendto(sock_fd, &m, sizeof(m), 0, (const struct sockaddr *) &client_addr, client_addr_size);
        }
        /* draw mark on new position */
        wmove(my_win, pos_x, pos_y);
        waddch(my_win,ch| A_BOLD);
        wrefresh(my_win);			
    }
  	endwin();			/* End curses mode		  */
    
	return 0;
}
