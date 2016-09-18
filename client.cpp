//client Stuff
#include "client.h"

int client::connectToServer(int port, char *host[]){
	//returns 0 on success
	portno = port;
	server = gethostbyname(*host);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		std::cout<<"Error: failed to open socket"<<std::endl;
		return 1;
	}
	if(server == NULL){
		std::cout<<"Error: no such host"<<std::endl;
		return 2;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
   	serv_addr.sin_family = AF_INET;
  	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   	serv_addr.sin_port = htons(portno);

   	   	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    	std::cout<<"Error: failed to connect to server"<<std::endl;
      	return 3;
   	}

   	std::cout<<"connected to server"<<std::endl;
   	return 0;

}

bool client::getServerData(){
	bzero(buffer,256);
	//blocking function
	n = recv(sockfd, buffer, sizeof(buffer),0); //first byte tells us the message type;
		
	if(n < 0){
		return false;
	}
	std::cout<<n<<std::endl;
	std::cout<<buffer[0]<<std::endl;

	switch(buffer[0]){

		case '0':
			return this->updatePlayerNames();
		case '1':
			return this->updatePlayerBid();
		case '2':
			return this->updatePlayerDieNumber();
		case '3':
			return this->Reroll();
		case '4':
			return this->makeBid();
		default:
			return false;
	}

}

bool client::updatePlayerNames(){
	std::cout<<"updatingPlayerNames"<<std::endl;
	char *position = &buffer[1];
	while(*position != '\0'){
		std::cout<<*position;
		++position;
	}
	std::cout<<std::endl;
	return true;
}

bool client::updatePlayerBid(){
	std::cout<<"updatePlayerBid"<<std::endl;
	return true;
}

bool client::updatePlayerDieNumber(){
	std::cout<<"updatePlayerDieNumber"<<std::endl;
	return true;
}

bool client::Reroll(){
	std::cout<<"Reroll"<<std::endl;
	return true;
}

bool client::makeBid(){
	std::cout<<"makeBid"<<std::endl;
	return true;
}
