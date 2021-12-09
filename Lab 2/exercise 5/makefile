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
PROG_NAME = $(SERVER_NAME) $(CLIENT_NAME)
# Dependencies
SERVER_OBJS = server.o 
SERVER_SOURCES =server.c funcs.c

CLIENT_OBJS = client.o
CLIENT_SOURCES = client.c 

 FUNCS_OBJS = funcs.o
 FUNCS_SOURCES = funcs.c

################################################################################
#                           Default and Common Tasks                           #
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
#                                Building Server                               #
################################################################################
$(SERVER_NAME):  $(SERVER_OBJS) $(FUNCS_OBJS)
	$(CC) $(MODE)  $(CFLAGS) -o $@  $(SERVER_OBJS)  $(FUNCS_OBJS)

$(CLIENT_NAME):  $(CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(CLIENT_OBJS)

funcs.o: $(FUNCS_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

server.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

client.o: $(CLIENT_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@
 
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

