//declaration of the s location
#define SOCK_ADDRESS "/tmp/sock_16"
// TODO_1
// declaration the struct corresponding to the exchanged messages
typedef enum direction_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction_t;
typedef struct message
{
    int msg_type; // message type| 0 == connection or do nothing | 1== movement or flash|
    int ch;
    direction_t direction;
} message;

typedef struct client
{
    int ch;
    int x;
    int y;
} clients;
