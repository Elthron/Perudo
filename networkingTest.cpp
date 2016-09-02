/*
compile with
g++ -std=c++14 networkingTest.cpp ThreadSafeList.h -o networkingTest -Werror -Wextra -Wall -O3
This server accepts 2 clients using a clientManger object. Then it uses the
broadcast method to send a message to all of the clients. It then uses the
whisper method to ask the client to something to the specified client. The 
super hacky bit of this is the \r character. This is used to notify the client
that it should send something back. The program hangs until it gets a response. 
This sort of thing could (should?) be delegated to a thread. It gets this response 
and broadcasts to everyone, then proceeds to ask the next client to say someething

To do: 
1.make the port number not hardcoded
2.Integrate into perudo to use players and the game loop. Thinking about the
structure of messages being sent may be important. We could use serialisation
if its a particularly complicated thing that needs to be sent over the port
3.get thready for threads

Know bugs:
1.sometimes when the program ends and is started again, the socket is unable to
bind,

The client program associated with this is clientSocket.c
*/
#include <string.h>
#include <iostream>
#include <list>
#include "clientManager.h"

int main(){

	std::list<int> client_ids;
	
	//add client manager to heap
	clientManager* foo = new clientManager(5001,&client_ids);
	
	while(client_ids.size()<2){
		foo->acceptJob();
	}

	std::string message = "Hello,World!";


	std::list<int>::iterator it;
	foo->broadcast(message);

	for(it = client_ids.begin(); it != client_ids.end(); ++it){
		foo->whisper("\rsay something",*it);
		foo->broadcast(foo->getResponse(*it));
	}


	delete foo;
	return 0;	
}
