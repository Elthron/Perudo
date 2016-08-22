#include <chrono>
#include <vector>
#include <list>
#include <utility>
#include <thread>
#include "Die.h"
#include "Player.h"
#include "wheel.h"
#include "ThreadSafeList.h"

//probably dont need all these, just here because im a lasy fuck
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <utility>
#include <iostream>


//functor to create players from client ids
class AddPlayer;

watchForClients(std::atomic<bool>& quit,ThreadSafeList& client_ids);

int main()
{
	//this was mostly shamefully plaigerised from http://www.tutorialspoint.com/unix_sockets/
	//set up the socket
	int sockfd, newsockfd, portno;
	unsigned int clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	//int  n;
   
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   	if (sockfd < 0) {
    	perror("ERROR opening socket");
      	exit(1);
   	}
   
   	/* Initialize socket structure */
   	bzero((char *) &serv_addr, sizeof(serv_addr));
   	portno = 5001; //this is the important thing thats clients need to know in order to join
   
   	serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = INADDR_ANY;
   	serv_addr.sin_port = htons(portno);
   
   	/* Now bind the host address using bind() call.*/
   	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    	perror("ERROR on binding");
      	exit(1);
   	}
	
	
	//seed the dice
	unsigned int seed=std::chrono::system_clock::now().time_since_epoch().count();
	Die::seed(seed);
	
	//empty wheel of players
	wheel<Player*> players;
	//functor to update the players
	AddPlayer addPlayer(players);
	
	//in this game a "bid" is a std::pair of ints: 4 2s -> std::pair<unsigned int,unsigned int> {4,2}
	typedef std::pair<unsigned int,unsigned int> Bid;
	//list of all the bids in the game
	std::list<Bid*> bids;
	//the bid of the next player
	Bid* next_bid=nullptr;
	
	//variable for totalling the dice counts during a challenge
	unsigned int total=0;
	
	//flag to control the while loops in both threads
	std::atomic<bool> quit(false);
	
	//thread-safe list of clients to be updated by a separate thread
	ThreadSafeList<int> client_ids;
	
	//start new thread to handle clients
	std::thread thread(watchForClients,quit,client_ids);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//main loop
	while(!quit.load())
	{
		//create the players
		client_ids.for_each(addPlayer);
		
		wheel::iterator player_it=players.begin();
		
		while(players.size()>1)
		{
			next_bid=player_it -> takeTurn( bids.back() );
			
			//if a bid was made, store it and move on to the next player's turn'
			if(next_bid)
			{
				bids.push_back(next_bid);
				continue;
			}
			
			//if no bid was made then a challenge has been levelled...
			
			total=0;
			for(unsigned int j=offset ; j<players.size() ; ++i)
			{
			//add the number of each appropriate die owned by the players to the total
			total+=players[j] -> countDice( (*bids.back()) -> second);
			}
			
			if( (*bids.back()) -> second <= total )
			{
				if( !( (*player_it) -> removeDice()) )
				{
					delete (player_it);
					players.erase( player_it + 1 );
				}
			}
			else
			{
				if( !(player_it-1 -> removeDice()) )
				{
					delete *(players_it-1);
					players.erase(player_it-1);
				}
			}
		}
		
		//reward winner
		
		//clean remaining player
		delete players.front();
		players.pop_back();
		
		
		//clean up bid array
		for(auto iter=bids.begin(), end=bids.end() ; iter!=end ; ++iter)
		{
			delete *iter;
			bids.erase(iter);
		}
		
	}
	
	//wait for the other thread to finish (which it should do soon as quit should now be set to true)
	thread.join();
	
	return 0;
}

class addPlayer
{
	public:
		addPlayer(wheel<Player*>& _players) : players(_players) {}
		
		void operator()(int client_id)
		{
			players.push_back(new Player(client_id));
		}
		
	private:
		wheel<Player*>& players;
};

//function to run in separate thread watching for new clientslisten(sockfd,5);

watchForClients(std::atomic<bool>& quit,ThreadSafeList<int>& client_ids
	int sockfd , int numOfConnections,  sockaddr_in &cli_addr)
{
	int client_id;
	
	while(!quit.load())
	{
		//added listen feature 22/08/16 jhb
		listen(sockfd,numOfConnections); 
		clilen = sizeof(cli_addr);
		/* Accept actual connection from the client */
		client_id = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if (client_id < 0) {
		//error handling
		}  
		if(/*something*/) client_ids.push_front(client_id);	//add the new client's id to the list
	}
}
