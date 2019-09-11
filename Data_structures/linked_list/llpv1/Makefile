# This is a simple Makefile

# Define what compiler to use and the flags

CC=gcc
#CFLAGS= -Wall -g -std=c99 -Werror -pthread
CFLAGS= -Wall -g -std=c99
TARGETS=main
EXCUTEABLE=binary

#From below line excution starts
all: clean ls $(TARGETS) $(EXCUTEABLE)

# Compile all .c files into ,o files 
# % matches all (like * in a command)
# $< is the source file (.c file)

$(TARGETS): main.o linkedlist.o miscell.o
	$(CC) -o main main.o linkedlist.o miscell.o

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#main.o: main.c linkedlist.h
#       $(CC) -c $<

#linkedlist.o: linkedlist.c linkedlist.h
#       $(CC) -c $<

$(EXCUTEABLE):$(TARGETS)
	./$(TARGETS)

clean:
	rm -f $(TARGETS) *.o

ls:
	ls -al

