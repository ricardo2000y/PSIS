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
SIMPLEX_CLIENT_NAME = SIMPLEX
DUPLEX_CLIENT_NAME = DUPLEX
PROG_NAME = $(SERVER_NAME) $(SIMPLEX_CLIENT_NAME) $(DUPLEX_CLIENT_NAME)
# Nomes para as fontes e objetos 
SERVER_OBJS = server-duplex.o 
SERVER_SOURCES =server-duplex.c 

SIMPLEX_CLIENT_OBJS = simplex_client.o
SIMPLEX_CLIENT_SOURCES = simplex_client.c 

DUPLEX_CLIENT_OBJS = duplex_client.o
DUPLEX_CLIENT_SOURCES = duplex_client.c 

################################################################################
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
# Compilacao e geracao de executaveis                               
################################################################################
$(SERVER_NAME):  $(SERVER_OBJS) 
	$(CC) $(MODE)  $(CFLAGS) -o $@  $(SERVER_OBJS) 

$(SIMPLEX_CLIENT_NAME):  $(SIMPLEX_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(SIMPLEX_CLIENT_OBJS)

$(DUPLEX_CLIENT_NAME):  $(DUPLEX_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(DUPLEX_CLIENT_OBJS)

server.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

simplex_client.o: $(SIMPLEX_CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

duplex_client.o: $(DUPLEX_CLIENT_SOURCES)
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

