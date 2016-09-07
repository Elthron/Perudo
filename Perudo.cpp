#include <chrono>
#include <vector>
#include <list>
#include <utility>
#include "clientManager.h"
#include "Die.h"
#include "Player.h"
#include "Wheel.h"
#include "Bid.h"

int main()
{
	//seed the dice
	unsigned int seed=std::chrono::system_clock::now().time_since_epoch().count();
	Die::seed(seed);
	
	//empty wheel of players
	wheel<Player*> players;
	
	//list of all the bids in the game
	std::list<Bid*> bids;
	//the bid of the next player
	Bid* next_bid=nullptr;
	
	//variable for totalling the dice counts during a challenge
	unsigned int total=0;
	
	//flag to control the while loop
	bool quit=false;
	
	//the client manager
	clientManager client_manager(8000);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//main loop
	while(!quit)
	{
		//create the players
		client_manager.populate(players);
		
		//roll the dice
		for(unsigned int i=0;i<players.size();++i)
		{
			players[i]->roll();
		}
		
		wheel<Player*>::iterator player_it=players.begin();
		
		while(players.size()>1)
		{
			next_bid=(*player_it) -> takeTurn( bids.back() );
			
			//if a bid was made, store it, broadcast it and move on to the next player's turn
			if(next_bid)
			{
				bids.push_back(next_bid);
				
				for(unsigned int i=0;i<players.size();++i)
				{
					players[i]->sendBid(next_bid);
				}
				
				continue;
			}
			
			//if no bid was made then a challenge has been levelled...
			
			total=0;
			for(unsigned int j=0 ; j<players.size() ; ++j)
			{
			//add the number of each appropriate die owned by the players to the total
			total+=players[j] -> countDice( bids.back() -> second);
			}
			
			if( bids.back() -> second <= total )
			{
				if( !( (*player_it) -> removeDice()) )
				{
					delete *player_it;
					players.erase(player_it);
				}
			}
			else
			{
				if( !(*(player_it-1)) -> removeDice())
				{
					delete *(player_it-1);
					players.erase(player_it-1);
				}
			}
			
			//once the challenge is completed, re-roll the dice
			for(unsigned int i=0;i<players.size();++i)
			{
				players[i]->roll();
			}
		}
		
		//reward winner
		
		//clean up the players
		for(unsigned int i=0;i<players.size();++i)
		{
			delete players.back();
			players.pop_back();
		}
		
		//clean up bid array
		for(auto iter=bids.begin(), end=bids.end() ; iter!=end ; ++iter)
		{
			delete *iter;
			bids.erase(iter);
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	return 0;
}