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

///////////////////////////////////////////////////////////////////////////////
class clientManager{
	
	std::list<int>* client_ids;
	int sockfd, newsockfd, portno;
   	unsigned int clilen;
   	char buffer[256];
   	struct sockaddr_in serv_addr, cli_addr;
   		
	
	public:
   		explicit clientManager(int port,std::list<int> *clients);
		
		void listenJob();
   		void broadcast();

};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
int main(){

	std::list<int> client_ids;
	//add client manager to heap
	clientManager* foo = new clientManager(5001,&client_ids);
	std::list<int>::iterator it;
	int i = 0;
	while(client_ids.size()<2 && i < 5){
		std::cout<<"Main: "<<client_ids.size()<<std::endl;
		foo->listenJob();
		++i;
	}

	for (it=client_ids.begin(); it != client_ids.end(); ++it){
		std::cout<<"Main: "<<*it<<std::endl;
	}

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

void clientManager::listenJob(){
    //this has no error checking what so ever.
  /*
	std::cout<<"listening for clients"<<std::endl;
	listen(sockfd,2);//hangs while waiting for clients, 
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	std::cout<<"client connected"<<std::endl;
	client_ids.push_front(newsockfd);//adds the new file descriptor to list
	*/
	std::list<int>::iterator it;
	client_ids->push_front(10);
	for (it=client_ids->begin(); it != client_ids->end(); ++it){
		std::cout<<"Manager: "<<*it<<std::endl;
	}
}


void clientManager::broadcast(){
	std::cout<<"broadcasting Message"<<std::endl;
}