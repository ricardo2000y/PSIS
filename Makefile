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
PROG_NAME = $(SERVER_NAME) $(HUMAN_CLIENT_NAME)$(MACHINE_CLIENT_NAME)
# Nomes para as fontes e objetos 
SERVER_OBJS = server.o 
SERVER_SOURCES =server.c 

HUMAN_CLIENT_OBJS = human_client.o
HUMAN_CLIENT_SOURCES = human_client.c 

MACHINE_CLIENT_OBJS = machine_client.o
MACHINE_CLIENT_SOURCES = machine_client.c 

################################################################################
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
# Compilacao e geracao de executaveis                               
################################################################################
$(SERVER_NAME):  $(SERVER_OBJS) 
	$(CC) $(MODE)  $(CFLAGS) -o $@  $(SERVER_OBJS) 

$(HUMAN_CLIENT_NAME):  $(HUMAN_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(HUMAN_CLIENT_OBJS)

$(MACHINE_CLIENT_NAME):  $(MACHINE_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(MACHINE_CLIENT_OBJS)

server.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

human_client.o: $(HUMAN_CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

machine_client.o: $(MACHINE_CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@
################################################################################
# limpeza de ficheiros inerentes a geracao do executavel  
################################################################################
.PHONY: clean cleanall
 
cleanall: clean cleanExe  

clean:
	rm -rf $(C_TRASH)  

cleanExe:
	rm -rf $(PROG_NAME)

