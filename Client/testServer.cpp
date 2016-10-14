/* this is for testing client functionality,
and not for anything else */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]){

	if(argc != 2){
		std::cout<<"Usage: <port> <messageType>"<<std::endl;
		return 1;
	}
	int sockfd, newsockfd, portno;
	unsigned int clilen;
   	char buffer[256];
   	const void *buf; // place in memory to be sent through the socket
   	struct sockaddr_in serv_addr,cli_addr;

   	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   	portno = atoi(argv[1]);

   	/* Initialize socket structure */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_family=AF_INET;

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
	  	perror("ERROR on binding");
	  	exit(1);
	}
	std::cout<<"Bound server to "<<portno<<std::endl;
	//get connection from client///////////////////////////////////////////////
	listen(sockfd,2);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	
	char received[255]; //stores stuff that comes from the client
	bzero(received,sizeof(received));
	int m = recv(newsockfd, received, sizeof(received),0);

	char *p; //print the clients name is
	p = &received[0];
	while(*p){
		std::cout<<*p;
		++p;
	}
	std::cout<<"connected"<<std::endl;
	///////////////////////////////////////////////////////////////////////////
	
	std::cout<<"sending data"<<std::endl;
	char message[255]; //this stores things to be sent to the client
	
	///////////////////////////* update player list *//////////////////////////
	std::string playerName(&received[0]);
	std::vector<std::string> playerList;

	playerList.push_back(std::string(playerName));
	playerList.push_back("hello");
	playerList.push_back("world");
	playerList.push_back("bar");
	playerList.push_back("foo");

	std::vector<std::string> cleanPlayerList(playerList); //this is wont have all those char 255 in it
	
	std::vector<std::string>::iterator iter;

	std::string temp;
	for (iter = playerList.begin(); iter != playerList.end(); ++iter)
	{
		//std::cout<<*iter<<'\t'<<iter->length()<<std::endl;
		*iter += (char) 255;
		temp += *iter;
		//std::cout<<(*iter)[sizeof(*iter->c_str())];
	}

	bzero(message,sizeof(message));
	unsigned char messageType = 5;
	unsigned char numberOfPlayers = 1;
	
	message[0] = (char) messageType;
	message[1] = (char) numberOfPlayers;

	std::cout<<temp.c_str()<<std::endl;

	strcpy(&message[2],temp.c_str());

	for(int i = 0; i < 255; ++i){
		std::cout<<message[i];
	}
	std::cout<<std::endl;

	int n = send(newsockfd,message,sizeof(message),0);
	std::cout<<"bytes sent: "<< n <<std::endl;

	/////////////////////////*make a bid*//////////////////////////////////////

	bzero(message,255);
	messageType = 1;
	unsigned char numberOfDice  = 2;
	unsigned char valueOfDice = 4;
	
	message[0] = (char) messageType;
	message[1] = (char) numberOfDice;
	message[2] = (char) valueOfDice;
	strcpy(&message[3],cleanPlayerList[1].c_str());
	
	message;
	
	n = send(newsockfd,message,sizeof(message),0);
	std::cout<<"bytes sent: "<< n <<std::endl;

	///////////////////////////////////////////////////////////////////////////

	
	///////////////////////////*Reroll your dice*//////////////////////////////
	bzero(message,255);
	messageType = 2;
	numberOfDice = 3;
	
	message[0] = (char) messageType;
	message[1] = (char) numberOfDice;
	message[2] = (char) 1;
	message[3] = (char) 1;
	message[4] = (char) 1;
	message[5] = (char) 1;
	message[6] = (char) 1;

	buf = message;

	n = send(newsockfd,buf,sizeof(message),0);
	std::cout<<"bytes sent: "<< n <<std::endl;

	///////////////////////////////////////////////////////////////////////////

	/////////////////////////////*player loses a dice *////////////////////////
	bzero(message,255);
	messageType = 3;
	
	message[0] = (char) messageType;
	strcpy(&message[1], cleanPlayerList[2].c_str());

	buf = message;

	n = send(newsockfd,buf,sizeof(message),0);

	std::cout<<"bytes sent: "<< n <<std::endl;
	///////////////////////////////////////////////////////////////////////////


	/////////////////*get a bid from the client*///////////////////////////////
	bzero(message,255);
	messageType = 4;
	message[0] = (char) messageType;

	n = send(newsockfd,message,sizeof(message),0);
	std::cout<<"bytes sent: "<< n <<std::endl;

	bzero(received,sizeof(received));
	bzero(message,255);
	
	m = recv(newsockfd, received, sizeof(received),0);

	messageType = 1;
	numberOfDice  = static_cast<unsigned char> (received[0]);
	valueOfDice = static_cast<unsigned char> (received[1]);
	
	message[0] = (char) messageType;
	message[1] = numberOfDice;
	message[2] = valueOfDice;
	strcpy(&message[3],playerName.c_str());
	
	message;
	
	n = send(newsockfd,message,sizeof(message),0);
	std::cout<<"bytes sent: "<< n <<std::endl;



	close(sockfd);

	return 0;
}