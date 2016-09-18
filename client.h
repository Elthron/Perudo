#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <utility> //pairs in here
#include <iostream>


class client{

	private:
		//things for storing socket info
		int sockfd, portno, n;
   		struct sockaddr_in serv_addr;
   		struct hostent *server;
   		unsigned char buffer[256];
   		//std::vector<std::pair<std::string name,int numberOfDice> > players;

   		//these methods will be called by getServerData
		bool updatePlayerNames();
		bool updatePlayerBid();
		bool updatePlayerDieNumber();
		bool Reroll();
		bool makeBid();

	public:
		int connectToServer(int port, char *host[]);

		
		//this one super method a way of calling other stuff;
		bool getServerData();

};

#endif