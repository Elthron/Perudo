#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <utility>
#include <iostream>
#include <list>
#include <cstring> 

class clientManager{
	
	private:
		std::list<int>* client_ids;
		std::list<int>::iterator it;
		
		//socket related stuff
		int sockfd, newsockfd, portno;
	   	unsigned int clilen;
	   	char buffer[256];
	   	const void *buf;
	   	struct sockaddr_in serv_addr, cli_addr;
	   
		

	public:
   		explicit clientManager(int port,std::list<int> *clients);
		~clientManager(); 
		//this needs stuff closing, havent worked out how to do that yet	
   		void broadcast(std::string message);
   		void whisper(std::string message, int clientfd); //send to specified client
   		void acceptJob(); //this method shall eventually have its own thread
   		std::string getResponse(int clientfd);
};

#endif