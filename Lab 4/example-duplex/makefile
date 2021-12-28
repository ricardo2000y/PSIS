################################################################################
#
# File Name: Makefile
#
#
# DESCRIPTION:
#
# USAGE:
#
################################################################################


################################################################################
#                                   Variables                                  #
################################################################################
# Compiler
CC = gcc
MODE = -g
CFLAGS = -Wall -pedantic -Wextra


# Cleaning
C_TRASH = *.o *.so
OBJS_CTRASH = $(addprefix , $(C_TRASH))
SO_CTRASH = $(addprefix , $(C_TRASH))

# Executables
SERVER_NAME = SERVER
CLIENT_NAME = CLIENT
#MACHINE_CLIENT_NAME = MACHINE
PROG_NAME = $(SERVER_NAME) $(CLIENT_NAME)
# Dependencies
SERVER_OBJS = server-duplex.o #SAO CRIADOS QUANDO COMPILAS
SERVER_SOURCES =server-duplex.c

CLIENT_OBJS = client-simplex.o
CLIENT_SOURCES = client-simplex.c 

#MACHINE_CLIENT_OBJS = machine_client.o
#MACHINE_CLIENT_SOURCES = server-duplex.c 

################################################################################
#                           Default and Common Tasks                           #
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
#                                Building Server                               #
################################################################################
$(SERVER_NAME):  $(SERVER_OBJS) 
	$(CC) $(MODE)  $(CFLAGS) -o $@  $(SERVER_OBJS) 

$(CLIENT_NAME):  $(CLIENT_OBJS)
	$(CC) $(MODE) $(CFLAGS) -o $@ $(CLIENT_OBJS)   

server-duplex.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

client-simplex.o: $(CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

#-L. -> FIFOS -> LNCURSES

################################################################################
#                                   Cleaning                                   #
################################################################################
# All tasks in this section are set as .PHONY
.PHONY: clean cleanAll cleanC  cleanExe 

clean: cleanC cleanExe 

cleanAll: clean 

cleanC:
	rm -rf $(C_TRASH) $(OBJS_CTRASH) $(SO_CTRASH)


cleanExe:
	rm -rf $(PROG_NAME)

