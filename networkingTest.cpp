#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <utility>
#include <iostream>
#include <list>
#include <thread>

#include "ThreadSafeList.h"
///////////////////////////////////////////////////////////////////////////////
class client{

   	int filedes;
   	char buffer[256];
public:

   	client(int connection);
   	std::pair<int,int> takeTurn(char play[2]);
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
class clientManager{

	int sockfd, newsockfd, portno;
   	unsigned int clilen;
   	char buffer[256];
   	struct sockaddr_in serv_addr, cli_addr;
	public:
   		explicit clientManager(ThreadSafeList<int>&);
   		~clientManager();

   		void listenJob();

   		void Broadcast();

};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int main(){

	//bens thread safe list
	ThreadSafeList<int> client_ids;

	clientManger foo = new clientManger(*client_ids);

	//start thread
	std::thread thread(foo.listenJob(),quit,client_ids);

	while(true){
		clientManager.Broadcast();
	}

	return 0;	
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
client::client(int connection){
   filedes = connection;
   bzero(buffer,256);
}

std::pair<int,int> client::takeTurn(char play[]){
   //the length of 2 ints
   //writes previous play to socket
   //needs to check if client still there
   const void *buf = play;
   write(filedes,buf,sizeof(buf));
   //reads the play 
   bzero(buffer,256);//clears the buffer
   read(filedes,buffer, 255);
   
   int i = buffer[0] - '0';
   int j = buffer[1] - '0';

   std::pair<int,int> bluf;
   bluf.first = i;
   bluf.second = j;

   return bluf;
}
///////////////////////////////////////////////////////////////////////////////

clientManager::clientManager(ThreadSafeList<int>& clients){
	ThreadSafeList<int> client_ids = *clients;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
	  	exit(1);
	}

	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 5001;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	  	perror("ERROR on binding");
	  	exit(1);
	}

}

void clientManager::listenJob(){
   //this has no error checking what so ever.
   while(true){
	   	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		client_ids.push_front(newsockfd);
	}
}

void clientManager::Broadcast(){
	for (std::list<int>::iterator it=client_ids.begin(); it != client_ids.end(); ++it)
    	write(*it,"hello World!",sizeof("hello World!"));
}