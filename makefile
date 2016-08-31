#compiler definition
CC = g++

#compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -O3 -pedantic

TARGET = networking

all: networking

networking: networkingTest.cpp
	$(CC) $(CFLAGS) -o networkingTest ThreadSafeList.cpp ThreadSafeList.h networkingTest.cpp

clean:
	$(RM) $(TARGET)