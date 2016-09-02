#include "clientManager.h"
//jhb 02/09/2016
//closes port now

clientManager::clientManager(int port, std::list<int> *clients){
	//to do: make initialiser list
	std::cout<<"creating client Manager"<<std::endl;

	client_ids = clients;

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

	for (it=client_ids->begin(); it != client_ids->end(); ++it){
		close(*it);
	}
	close(sockfd);
}


void clientManager::acceptJob(){
    //this has no error checking what so ever.
	std::cout<<"listening for clients"<<std::endl;
	listen(sockfd,2);//hangs while waiting for clients, 
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	std::cout<<"client connected: fd= "<< newsockfd <<std::endl;
	client_ids->push_front(newsockfd);//adds the new file descriptor to list
	std::cout<<sizeof(client_ids)<<std::endl;
}


void clientManager::broadcast(std::string message){
	//sends the same message to every client
	//at the moment it can only send 8 chars for some reason
	int n; //test number to check if the message was sent
	std::cout<<"broadcasting Message: "<<message<<std::endl;

	buf = message.c_str(); //relic of c? obtain a pointer to c char array

	for (it=client_ids->begin(); it != client_ids->end(); ++it){
		n = send(*it,buf,sizeof(message),0);
		std::cout<<sizeof(buf)<<"\t"<<n<<std::endl;

		if(n<0){
			std::cout<<"something went horribly wrong"<<std::endl;
		}
	}
	bzero((void*) buf,sizeof(buf));

}

void clientManager::whisper(std::string message, int clientfd){
	//sends the same message to every client
	//at the moment it can only send 8 chars for some reason
	int n; //test number to check if the message was sent
	std::cout<<"whispering "<<message<<std::endl;
	
	buf = message.c_str(); //relic of c? obtain a pointer to c char array

	n = send(clientfd,buf,sizeof(message),0);
	std::cout<<sizeof(buf)<<"\t"<<n<<std::endl;

	if(n<0){
		std::cout<<"something went horribly wrong"<<std::endl;
	}

}

std::string clientManager::getResponse(int clientfd){
	int n;
	bzero(buffer,sizeof(buffer));
    n = recv(clientfd, buffer, sizeof(buf),0);
   	//std::cout<<n<<"\t"<<buffer<<std::endl;
   	if(n<0){
   		return "failed to get response";
   	}
    return buffer;
}
