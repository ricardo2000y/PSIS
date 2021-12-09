################################################################################
#
# File Name: Makefile
#
# Authors:
#      	Diogo Lemos Fernandes (ist190056)
#      	Tiago Lopes Rocha (ist190194)
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

# Dirs
OBJS_DIR = objs/
SO_DIR = so/
DIRS = $(OBJS_DIR) $(SO_DIR)

# Cleaning
C_TRASH = *.o *.so
OBJS_CTRASH = $(addprefix $(OBJS_DIR), $(C_TRASH))
SO_CTRASH = $(addprefix $(SO_DIR), $(C_TRASH))

# Executables
PROG_NAME_SERVER = lab03_1server
PROG_NAME_HUMAN = lab03_1human
PROGS_NAME = $(PROG_NAME_SERVER) $(PROG_NAME_HUMAN)

# Complementary files to executables
SERVER_FIFO = /tmp/lab03_1_fifoServer
FIFOS = $(SERVER_FIFO)

# Dependencies
SERVER_OBJS = $(OBJS_DIR)server.o
SERVER_SOURCES = server.c

HUMAN_OBJS = $(OBJS_DIR)human.o
HUMAN_SOURCES = human-control-client.c


################################################################################
#                           Default and Common Tasks                           #
################################################################################
.PHONY: default
default: $(PROGS_NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(SO_DIR):
	mkdir -p $(SO_DIR)


################################################################################
#                                Building Server                               #
################################################################################
$(PROG_NAME_SERVER): $(DIRS) $(SERVER_OBJS)
	$(CC) $(MODE) $(CFLAGS) -o $@ $(SERVER_OBJS) -lncurses

$(OBJS_DIR)server.o: $(SERVER_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@


################################################################################
#                                Building Human                               #
################################################################################
$(PROG_NAME_HUMAN): $(DIRS) $(HUMAN_OBJS)
	$(CC) $(MODE) $(CFLAGS) -o $@ $(HUMAN_OBJS) -lncurses

$(OBJS_DIR)human.o: $(HUMAN_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@


################################################################################
#                                   Cleaning                                   #
################################################################################
# All tasks in this section are set as .PHONY
.PHONY: clean cleanAll cleanC cleanDir cleanExe cleanFifo

clean: cleanC cleanExe cleanFifo

cleanAll: clean cleanDir

cleanC:
	rm -rf $(C_TRASH) $(OBJS_CTRASH) $(SO_CTRASH)

cleanDir:
	rm -rf $(DIRS)

cleanExe:
	rm -rf $(PROGS_NAME)

cleanFifo:
	-$(foreach fifo, $(FIFOS), unlink $(fifo);)
