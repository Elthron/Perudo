#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "Bid.h"
#include "player.h"


class client{

	private:
		//things for storing socket info
		int sockfd, portno, n;
   		struct sockaddr_in serv_addr;
   		struct hostent *server;
   		unsigned char buffer[255]; //data to send
   		char recbuf[255]; //probs dont need this

   		//game info
   		std::vector<player*>* pplayerVector;
   		self* pself;


   		//these methods will be called by getServerData
		bool updatePlayerNames();
		bool updatePlayerBid();
		bool updatePlayerDieNumber();
		bool Reroll();
		bool makeBid();

	public:
		int connectToServer(int port, char *host[],std::string name);

		explicit client(std::vector<player*>* p, self* me);
		
		//this one super method a way of calling other stuff;
		bool getServerData();

		void testFunc();

};


#endif
