// TODO_1 
// declaration the struct corresponding to the exchanged messages
typedef struct message {
    int msg_type;
    char ch;
}message;
// TODO_2
//declaration of the FIFO location
char const* fifo_loc= "/tmp/fifo_lab3_1";

typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;