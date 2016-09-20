#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "Bid.h"

struct playerInfo{
	int numberOfDice;
	std::string name;
	Bid bid;
};

class client{

	private:
		//things for storing socket info
		int sockfd, portno, n;
   		struct sockaddr_in serv_addr;
   		struct hostent *server;
   		unsigned char buffer[255];
   		
   		//game info
   		std::vector<playerInfo> players;
   		int numberOfPlayers;
   		int numberOfDice;
   		std::vector<int> dice;

   		//these methods will be called by getServerData
		bool updatePlayerNames();
		bool updatePlayerBid();
		bool updatePlayerDieNumber();
		bool Reroll();
		bool makeBid();

	public:
		int connectToServer(int port, char *host[]);

		explicit client();
		//this one super method a way of calling other stuff;
		bool getServerData();

};


#endif