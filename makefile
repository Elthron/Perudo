#this is the makefile used to compile the server

#compiler/flag macros
CXX=g++
CPPFLAGS=-Wall -Werror -Wextra -std=c++14 -O3 -pthread

#objects macro
OBJECTS=Perudo.o Player.o Die.o Bid.o clientManager.o Human.o Message.o
#---------------------------------------------------------------------

#main rule
Server: $(OBJECTS)
	$(CXX) $(OBJECTS) $(CPPFLAGS) -o Server $(LDFLAGS)

#supporting rules
Perudo.o: Die.h Player.h Wheel.h Bid.h Message.h
Player.o: Player.h Die.h Bid.h
Die.o: Die.h
Bid.o: Bid.h
clientManager.o: clientManager.h ThreadSafeList.h Human.h Message.h
Human.o: Human.h Player.h clientManager.h Message.h
Message.o: Message.h

.PHONY: clean
clean:
	rm Server *.o *~
