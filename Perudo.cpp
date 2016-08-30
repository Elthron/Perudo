#include <chrono>
#include <vector>
#include <list>
#include <utility>
#include <thread>
#include "Die.h"
#include "Player.h"
#include "Wheel.h"
#include "ThreadSafeList.h"
#include "Bid.h"

//functor to create players from client ids
class AddPlayer;

watchForClients(std::atomic<bool>& quit,ThreadSafeList& client_ids);

int main()
{
	//seed the dice
	unsigned int seed=std::chrono::system_clock::now().time_since_epoch().count();
	Die::seed(seed);
	
	//empty wheel of players
	wheel<Player*> players;
	//functor to update the players
	AddPlayer addPlayer(players);
	
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
			
			//if a bid was made, store it, broadcast it and move on to the next player's turn
			if(next_bid)
			{
				bids.push_back(next_bid);
				
				for(unsigned int i=0;i<players.size();++i)
				{
					players[i].sendBid(next_bid);
				}
				
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
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//wait for the other thread to finish (which it should do soon as quit should now be set to true)
	thread.join();
	
	return 0;
}

//function to run in separate thread watching for new clients
watchForClients(std::atomic<bool>& quit,ThreadSafeList<int>& client_ids)
{
	int client_id;
	
	while(!quit.load())
	{
		//search for new clients somehow...
		
		if(/*something*/) client_ids.push_front(client_id);	//add the new client's id to the list
	}
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
