#this is the make file for Perudo

#compiler definition
CC = g++

#compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -O3 -pedantic

all: Perudo

#object files needed for Perudo
Perudo: Perudo.o Die.o Player.o Wheel.o ThreadSafeList.o Bid.o
	$(CC) $(CFLAGS) -o Perudo Perudo.o Die.o Player.o Wheel.o ThreadSafeList.o Bid.o

Basic_AI.o: Basic_AI.cpp Player.h
	$(CC) $(CFLAGS) -c Basic_AI.cpp

Player.o: Player.cpp Die.h Bid.h
	$(CC) $(CFLAGS) -c Player.cpp

#remove all old o files
clean: 
	$(RM) Perudo *.o *~
