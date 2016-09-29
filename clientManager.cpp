#include <stdexcept>
#include "clientManager.h"
#include "Message.h"
//jhb 02/09/2016
//closes port now

clientManager::clientManager(int port):
	sockfd(socket(AF_INET, SOCK_STREAM, 0)),
	portno(port),
	thread(acceptJob,sockfd,newsockfd,clilen,cli_addr,&client_ids)
{
	std::cout<<"finalising client Manager creation"<<std::endl;
	
	//detach the main client recieving thread there being no way to stop it
	thread.detach();
	
	int random_int=1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &random_int, sizeof(int)) <0 ){
		throw std::domain_error("setsockopt messed up");
	}
	
	if (sockfd < 0) {
		throw std::domain_error("error opening socket");
	}
	
	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_family=AF_INET;
	
	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		throw std::domain_error("error on binding");
	}
	
	std::cout<<"Bound server to "<<portno<<std::endl;
}

clientManager::~clientManager(){
	std::cout<<"Destroying client manager:"<<std::endl;
	
	//instantiate an instance of CloseClients and perform it on the list
	std::cout<<"\tClosing sockets..."<<std::endl;
	CloseClients closeClients;
	client_ids.for_each<CloseClients>(closeClients);
	
	//close the main socket
	close(sockfd);
	
	std::cout<<"\tDone."<<std::endl;
}

void clientManager::populate(wheel<Player*>& wheel){
	//create a functor instance
	AddPlayer addPlayer(wheel);
	//iterate it over the client ids
	client_ids.for_each<AddPlayer>(addPlayer);
}

void clientManager::acceptJob(int _sockfd, int _newsockfd, unsigned int _clilen, sockaddr_in _cli_addr, ThreadSafeList<int>* _client_ids){
    while(true){
		//this has no error checking what so ever.
		
		//hang while waiting for clients
		std::cout<<"listening for clients..."<<std::endl;
		listen(_sockfd,2);
		
		_clilen = sizeof(_cli_addr);
		_newsockfd = accept(_sockfd, (struct sockaddr *)&_cli_addr, &_clilen);
		std::cout<<"client connected: fd= "<< _newsockfd <<std::endl;
		
		//adds the new file descriptor to list
		_client_ids->push_front(_newsockfd);
		
		//basic throttling to reduce overheating/processor-hogging
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
	std::cout<<"\tAccept job loop ended."<<std::endl;
}

void clientManager::whisper(Message& message, int clientfd){
	//sends a message to a client
	
	int n; //test number to check if the message was sent
	
	n = send(clientfd,message.getMessage(),message.getSize(),0);
	std::cout<<sizeof(buf)<<"\t"<<n<<std::endl;
	
	if(n<0){
		std::cout<<"something went horribly wrong"<<std::endl;
	}
}

void clientManager::broadcast(Message& message){
	//create functor
	Broadcast broadcastMessage(message,*this);
	//iterate over clients
	client_ids.for_each<Broadcast>(broadcastMessage);
}

std::string clientManager::getResponse(int clientfd){
	int n;
	bzero(buffer,sizeof(buffer));
        n = recv(clientfd, buffer, sizeof(buf),0);
   	
   	if(n<0){
   		return "failed to get response";
   	}
    return buffer;
}
