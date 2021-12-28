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
HUMAN_CLIENT_NAME = HUMAN
MACHINE_CLIENT_NAME = MACHINE
PROG_NAME = $(SERVER_NAME) $(HUMAN_CLIENT_NAME) $(MACHINE_CLIENT_NAME)
# Dependencies
SERVER_OBJS = server.o 
SERVER_SOURCES =server.c 

HUMAN_CLIENT_OBJS = human_client.o
HUMAN_CLIENT_SOURCES = human_client.c 

MACHINE_CLIENT_OBJS = machine_client.o
MACHINE_CLIENT_SOURCES = machine_client.c 

################################################################################
#                           Default and Common Tasks                           #
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
#                                Building Server                               #
################################################################################
$(SERVER_NAME):  $(SERVER_OBJS) 
	$(CC) $(MODE)  $(CFLAGS) -o $@  $(SERVER_OBJS) -lcurses -lncurses

$(HUMAN_CLIENT_NAME):  $(HUMAN_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(HUMAN_CLIENT_OBJS) -lcurses -lncurses

$(MACHINE_CLIENT_NAME):  $(MACHINE_CLIENT_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(MACHINE_CLIENT_OBJS) -lcurses -lncurses

server.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@ -lcurses -lncurses

human_client.o: $(HUMAN_CLIENT_SOURCES) -lcurses -lncurses
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

#machine_client.o: $(MACHINE_CLIENT_SOURCES) -lcurses -lncurses
#	$(CC) $(MODE) $(CFLAGS) -c $< -o $@
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

