#this is the make file for the perudo client

#compiler definition
CC = g++

#compiler flags
CFLAGS = -std=c++14 -Wall -Wextra -Werror -O3 -pedantic

#linker flags
LDFLAGS = -lcurses

#objects list
OBJECTS = testClient.o client.o Bid.o

#main rule
all: Client
Client: $(OBJECTS)
	$(CC) $(CFLAGS) -o Client $(OBJECTS) $(LDFLAGS)

#supporting rules
testClient.o: client.h
client.o: client.h Bid.h
Bid.o: Bid.h

#remove all old o files
clean: 
	$(RM) Client *.o *~
