################################################################################
# Makefile
# Descrição:
# forma simples e intuitiva de compilar o código, de fácil edição.
################################################################################
# Nomes de variaveis usadas ao longo do Makefile 
################################################################################

# variaveis do compilador
CC = gcc
MODE = -g
CFLAGS = -Wall -pedantic -Wextra

# Variaveis para limpeza de ficheiros inerentes a geracao do executavel 
C_TRASH = *.o *.so
OBJS_CTRASH = $(addprefix , $(C_TRASH))
SO_CTRASH = $(addprefix , $(C_TRASH))

# Nomes para os executaveis 
SERVER_NAME = SERVER
HUMAN_CLIENT_NAME = HUMAN
MACHINE_CLIENT_NAME = MACHINE
REMOTE_DISP_NAME = DISPLAY
PROG_NAME = $(SERVER_NAME) $(HUMAN_CLIENT_NAME) $(MACHINE_CLIENT_NAME) $(REMOTE_DISP_NAME)
# Nomes para as fontes e objetos 
SERVER_OBJS = server.o 
SERVER_SOURCES =server.c 

HUMAN_CLIENT_OBJS = human_client.o
HUMAN_CLIENT_SOURCES = human_client.c 

MACHINE_CLIENT_OBJS = machine_client.o
MACHINE_CLIENT_SOURCES = machine_client.c 

DISPLAY_OBJS= remote-display-client.o
DISPLAY_SOURCES= remote-display-client.c
################################################################################
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
# Compilacao e geracao de executaveis                               
################################################################################
$(SERVER_NAME):  $(SERVER_OBJS) 
	$(CC) $(MODE)  $(CFLAGS) -o $@  $(SERVER_OBJS) -lcurses -lncurses

$(HUMAN_CLIENT_NAME):  $(HUMAN_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(HUMAN_CLIENT_OBJS) -lcurses -lncurses

$(MACHINE_CLIENT_NAME):  $(MACHINE_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(MACHINE_CLIENT_OBJS) -lcurses -lncurses

$(REMOTE_DISP_NAME):  $(DISPLAY_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(DISPLAY_OBJS) -lcurses -lncurses

server.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@ -lcurses -lncurses

human_client.o: $(HUMAN_CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@ -lcurses -lncurses

machine_client.o: $(MACHINE_CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@ -lcurses -lncurses

remote-display-client.o: $(DISPLAY_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@ -lcurses -lncurses
################################################################################
# limpeza de ficheiros inerentes a geracao do executavel  
################################################################################
.PHONY: clean cleanall
 
cleanall: clean cleanExe  

clean:
	rm -rf $(C_TRASH)  

cleanExe:
	rm -rf $(PROG_NAME)

