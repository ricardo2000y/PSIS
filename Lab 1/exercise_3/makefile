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
PROG_NAME= lab01_3


# Dependencies
PROG1_OBJS = prog1.o
PROG1_SOURCES = prog1.c lib.h

LIB1_OBJS = lib1.o
LIB1_SOURCES = lib1.c lib.h


################################################################################
#                           Default and Common Tasks                           #
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
#                                Building Server                               #
################################################################################
$(PROG_NAME):  $(LIB1_OBJS) $(PROG1_OBJS)
	$(CC) $(MODE) $(CFLAGS) -o $@ $(LIB1_OBJS) $(PROG1_OBJS)

lib1.o: $(LIB1_SOURCES)
	$(CC) $(MODE) $(CFLAGS) -c $< -o $@

prog1.o: $(PROG1_SOURCES)
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

