#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <utility>
#include <iostream>
#include <list>
#include <cstring>
#include <thread>
#include "ThreadSafeList.h"
#include "Wheel.h"
#include "Human.h"

class Message;

class clientManager{
	private:
		//socket related stuff
		int sockfd, newsockfd, portno;
		unsigned int clilen;
	   	char buffer[256];
	   	const void *buf;
	   	struct sockaddr_in serv_addr,cli_addr;
		
		//threading stuff
		std::thread thread;
		ThreadSafeList<int> client_ids;
		
		static void acceptJob(int _sockfd, int _newsockfd, unsigned int _clilen, sockaddr_in _cli_addr, ThreadSafeList<int>* _client_ids); //this method has its own thread
		
	public:
   		explicit clientManager(int port);
		~clientManager();
		
		//function to populate a wheel object with players from the thread safe list
		void populate(wheel<Player*>& wheel);
   		void whisper(Message& message, int clientfd); //send to specified client
		void broadcast(Message& message); //send to all clients
   		std::string getResponse(int clientfd);
};

//functor to close a client (used in d/tor)
struct CloseClients{
	explicit CloseClients(){}
	void operator()(int client) {close(client);}
};

//functor to create players from client ids
class AddPlayer
{
	public:
		AddPlayer(wheel<Player*>& _players) : players(_players) {}
		
		void operator()(int client_id)
		{
			players.push_back(new Human(client_id));
		}
		
	private:
		wheel<Player*>& players;

};

//fucntor to whisper a message to all clients
class Broadcast
{
	public:
		Broadcast(Message& _message,clientManager& _mgr) : message(_message),mgr(_mgr) {}
		
		void operator()(int client_id)
		{
			mgr.whisper(message,client_id);
		}
		
	private:
		Message& message;
		clientManager& mgr;
};

#endif