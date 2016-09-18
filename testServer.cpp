/* this is for testing client functionality,
and not for anything else */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

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

	unsigned char message[] = "012a";// \0
	buf = message;

	int n = send(newsockfd,buf,sizeof(message),0);
	std::cout<<n<<std::endl;
	close(sockfd);

	return 0;
}