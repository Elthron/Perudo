/*
compile with
g++ -std=c++14 networkingTest.cpp ThreadSafeList.h -o networkingTest -Werror -Wextra -Wall -O3

This server accepts clients using a clientManger object. The aim of this is
to make a way of simultaneously listening for clients and broadcasting to them.
Know bugs:
1.sometimes when the program ends and is started again, the socket is unable to
bind, this is probably something to do with not closing the socket

Eventually clientManager will be in its own cpp

The client program associated with this is clientSocket.c
*/

#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <utility>
#include <iostream>
#include <list>
#include <cstring> 
#include <thread>
#include "ThreadSafeList.h"

///////////////////////////////////////////////////////////////////////////////
class clientManager{
	
	private:
		ThreadSafeList<int>* client_ids;
		
		//socket related stuff
		int sockfd, newsockfd, portno;
	   	unsigned int clilen;
	   	char buffer[256];
	   	struct sockaddr_in serv_addr, cli_addr;
	   
		void _listenJob(); //this method shall eventually have its own thread

	public:
   		explicit clientManager(int port,ThreadSafeList<int> *clients);
		~clientManager(); 
		//this needs stuff closing, havent worked out how to do that yet	
   		void broadcast(std::string message,int clientfd); //send to specified client
   		std::thread start();
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int main(){

	ThreadSafeList<int> client_ids;
	
	//add client manager to heap
	clientManager* foo = new clientManager(5001,&client_ids);
	
	foo->start();

	std::string message = "Hello,World!";
	
	delete foo;
	return 0;	
}

///////////////////////////////////////////////////////////////////////////////

clientManager::clientManager(int port, ThreadSafeList<int> *clients){
	//to do: make initialiser list
	std::cout<<"creating client Manager"<<std::endl;
	
	client_ids = clients;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* First call to socket() function */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
	  	perror("ERROR opening socket");
	 	exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = port;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	  	perror("ERROR on binding");
	  	exit(1);
	}
	std::cout<<"Bound server to "<<portno<<std::endl;
}

clientManager::~clientManager(){


}
void clientManager::_listenJob(){
    //this has no error checking what so ever.
	while(true){
		std::cout<<"listening for clients"<<std::endl;
		listen(sockfd,2);//hangs while waiting for clients, 
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		std::cout<<"client connected"<<std::endl;
		client_ids->push_front(newsockfd);//adds the new file descriptor to list
		std::cout<<sizeof(client_ids)<<std::endl;
	}
}


void clientManager::broadcast(std::string message, int clientfd){
	//sends specified message to a single client
	
	int n; //test number to check number of bytes sent
	std::cout<<"broadcasting Message: "<<message<<std::endl;

	const void *buf = message.c_str(); //relic of c? obtain a pointer to c char array

	n = write(clientfd,buf,sizeof(message));
	std::cout<<sizeof(message)<<"\t"<<n<<std::endl;
	if(n<0){
		std::cout<<"something went horribly wrong"<<std::endl;
	}
	
	
}
std::thread clientManager::start(){
//stolen from http://stackoverflow.com/questions/10673585/start-thread-with-member-function
	return std::thread( [this] { this->_listenJob(); } );
}
