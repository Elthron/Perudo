/* this is for testing client functionality,
and not for anything else */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <array>

int main(int argc, char *argv[]){

	if(argc != 2){
		std::cout<<"Usage: <port> <messageType>"<<std::endl;
		return 1;
	}
	int sockfd, newsockfd, portno;
	unsigned int clilen;
   	char buffer[256];
   	const void *buf;
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

	listen(sockfd,2);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	std::cout<<"sending data"<<std::endl;
	//I want to write the second bit of the message as 0 - 255 rather than "1"

	char message[255];
	/*this is the way to send a message... its not super easy atm
	but the idea works*/
	
	/* update player list */
	char foo[] = "12345678";
	unsigned char messageType = 0;
	unsigned char numberOfPlayers = 1;
	
	message[0] = (char) messageType;
	message[1] = (char) numberOfPlayers;
	strcpy(&message[2],foo);
	
	buf = message;
	
	int n = send(newsockfd,buf,sizeof(message),0);
	
	std::cout<<n<<std::endl;	

	/* make a bid */
	bzero(message,255);
	messageType = 1;
	unsigned char numberOfDice  = 2;
	unsigned char valueOfDice = 4;
	char name[] = "12345678";
	
	message[0] = (char) messageType;
	message[1] = (char) numberOfDice;
	message[2] = (char) valueOfDice;
	strcpy(&message[3],name);
	
	buf = message;

	n = send(newsockfd,buf,sizeof(message),0);
	std::cout<<n<<std::endl;
	
	/*Reroll your dice*/
	bzero(message,255);
	messageType = 2;
	numberOfDice = 5;
	
	message[0] = (char) messageType;
	message[1] = (char) numberOfDice;
	message[2] = (char) 1;
	message[3] = (char) 2;
	message[4] = (char) 3;
	message[5] = (char) 4;
	message[6] = (char) 5;

	buf = message;
	n = send(newsockfd,buf,sizeof(message),0);
	std::cout<<n<<std::endl;

	/*player loses a dice */
	bzero(message,256);
	messageType = 3;
	char playerName[] = "12345678";
	
	message[0] = (char) messageType;
	strcpy(&message[1], playerName);

	buf = message;
	n = send(newsockfd,buf,sizeof(message),0);
	std::cout<<n<<std::endl;

	close(sockfd);

	return 0;
}