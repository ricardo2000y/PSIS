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
PROG_NAME= lab01_4


# Dependencies
MAIN_OBJS = main.o 
MAIN_SOURCES = main.c lib.h

LIB1_OBJS = lib1.so
LIB1_SOURCES = lib1.c lib.h

LIB2_OBJS = lib2.so
LIB2_SOURCES = lib2.c lib.h

################################################################################
#                           Default and Common Tasks                           #
################################################################################
.PHONY: default
default: $(PROG_NAME)

################################################################################
#                                Building Server                               #
################################################################################
$(PROG_NAME):  $(LIB1_OBJS) $(LIB2_OBJS) $(MAIN_OBJS)
	$(CC) $(MODE) -L. $(CFLAGS) -o $@ $(MAIN_OBJS) -ldl $(LIB1_OBJS) $(LIB2_OBJS) 

lib1.so: $(LIB1_SOURCES)
	$(CC) -shared $(MODE) $(CFLAGS) -fPIC  $< -o $@

lib2.so: $(LIB2_SOURCES)
	$(CC) -shared $(MODE) $(CFLAGS) -fPIC  $< -o $@

	
main.o: $(MAIN_SOURCES)
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

