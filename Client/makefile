#this is the make file for Perudo client

#compiler definition
CC = g++

#compiler flags
CFLAGS = -std=c++14 -Wall -Wextra -Werror -O3 -pedantic

#objects list
OBJECTS = 

all: Client

#object files needed for Perudo
Client: $(OBJECTS)
	$(CC) $(CFLAGS) -o Client $(OBJECTS)

#remove all old o files
clean: 
	$(RM) Client *.o *~
