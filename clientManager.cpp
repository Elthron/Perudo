#include "clientManager.h"
#include "Message.h"
//jhb 02/09/2016
//closes port now

clientManager::clientManager(int port):
	sockfd(socket(AF_INET, SOCK_STREAM, 0)),
	portno(port),
	quit(false),
	thread(acceptJob,sockfd,newsockfd,clilen,cli_addr,&client_ids,&quit)
{
	std::cout<<"finalising client Manager creation"<<std::endl;
	
	//set human object static member
	Human::setMgr(this);
	
	if (sockfd < 0) {
	  	perror("ERROR opening socket");
	 	exit(1);
	}
	
	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_family=AF_INET;
	
	/* Now bind the host address using bind() call.*/
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	  	perror("ERROR on binding");
	  	exit(1);
	}
	
	std::cout<<"Bound server to "<<portno<<std::endl;
}

clientManager::~clientManager(){
	//turn off the thread and wait for it to finish - make sure this is always first
	quit.store(true);
	thread.join();
	
	//instantiate an instance of CloseClients and perform it on the list
	CloseClients closeClients;
	client_ids.for_each<CloseClients>(closeClients);
	
	close(sockfd);
}

void clientManager::populate(wheel<Player*>& wheel){
	//create a functor instance
	AddPlayer addPlayer(wheel);
	//iterate it over the client ids
	client_ids.for_each<AddPlayer>(addPlayer);
}

void clientManager::acceptJob(int _sockfd, int _newsockfd, unsigned int _clilen, sockaddr_in _cli_addr, ThreadSafeList<int>* _client_ids, std::atomic<bool>* _quit){
    while( !( _quit->load() ) ){
		//this has no error checking what so ever.
		std::cout<<"listening for clients"<<std::endl;
		listen(_sockfd,2);//hangs while waiting for clients, 
		_clilen = sizeof(_cli_addr);
		_newsockfd = accept(_sockfd, (struct sockaddr *)&_cli_addr, &_clilen);
		std::cout<<"client connected: fd= "<< _newsockfd <<std::endl;
		_client_ids->push_front(_newsockfd);//adds the new file descriptor to list
		std::cout<<sizeof(*_client_ids)<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));//basic throttling to reduce overheating/processor-hogging
	}
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
