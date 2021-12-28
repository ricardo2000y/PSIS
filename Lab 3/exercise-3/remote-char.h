// TODO_1 
// declaration the struct corresponding to the exchanged messages
typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;
typedef struct message {
    int msg_type;
    char ch;
    direction_t direction;
}message;
// TODO_2
//declaration of the FIFO location
char const* fifo_loc= "/tmp/fifo_lab3_1";

