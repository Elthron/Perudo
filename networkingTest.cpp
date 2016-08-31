/*
compile with
g++ -std=c++14 networkingTest.cpp -o networkingTest -Werror -Wextra -Wall -O3

This server accepts 2 clients using a clientManger object. The aim of this is
to make a way of handling more than one client. This particular example allows
2 clients and broadcasts the same message to all of them. There are a couple of
know bugs:
1.sometimes when the program ends and is started again, the socket is unable to
bind, this is probably something to do with not closing the socket
2.It only writes the first 8 characters of the message, no idea why

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

///////////////////////////////////////////////////////////////////////////////
class clientManager{
	
	std::list<int>* client_ids;
	std::list<int>::iterator it;
	
	//socket related stuff
	int sockfd, newsockfd, portno;
   	unsigned int clilen;
   	char buffer[256];
   	struct sockaddr_in serv_addr, cli_addr;
   		
	public:
   		explicit clientManager(int port,std::list<int> *clients);
		~clientManager(); 
		//this needs stuff closing, havent worked out how to do that yet
		
		void listenJob(); //this method shall eventually have its own thread
   		void broadcast(std::string message); //send a message to all clients

};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int main(){

	std::list<int> client_ids;
	
	//add client manager to heap
	clientManager* foo = new clientManager(5001,&client_ids);
	
	std::list<int>::iterator it;
	
	//wait for 2 clients
	while(client_ids.size()<2){
		std::cout<<"Main: "<<client_ids.size()<<std::endl;
		foo->listenJob();
	}
	
	std::string message = "Hello,World!";
	foo->broadcast(message);

	delete foo;
	return 0;	
}

///////////////////////////////////////////////////////////////////////////////

clientManager::clientManager(int port, std::list<int> *clients){
	std::cout<<"creating client Manager"<<std::endl;
	
	client_ids = clients;
	std::list<int>::iterator it;
	
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
void clientManager::listenJob(){
    //this has no error checking what so ever.

	std::cout<<"listening for clients"<<std::endl;
	listen(sockfd,2);//hangs while waiting for clients, 
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	std::cout<<"client connected"<<std::endl;
	client_ids->push_front(newsockfd);//adds the new file descriptor to list
	
	std::list<int>::iterator it;
	for (it=client_ids->begin(); it != client_ids->end(); ++it){
		std::cout<<"Manager: "<<*it<<std::endl;
	}
}


void clientManager::broadcast(std::string message){
	//sends the same message to every client
	//at the moment it can only send 8 chars for some reason
	int n; //test number to check if the message was sent
	std::cout<<"broadcasting Message: "<<message<<std::endl;

	const void *buf = message.c_str(); //relic of c? obtain a pointer to c char array

	for (it=client_ids->begin(); it != client_ids->end(); ++it){
		n = write(*it,buf,sizeof(buf));
		std::cout<<sizeof(buf)<<"\t"<<n<<std::endl;

		if(n<0){
			std::cout<<"something went horribly wrong"<<std::endl;
		}
	}
}
