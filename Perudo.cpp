#include <chrono>
#include <vector>
#include <list>
#include <utility>
#include <thread>
#include <iostream>
#include "clientManager.h"
#include "Die.h"
#include "Player.h"
#include "Wheel.h"
#include "Bid.h"

void perudo();

//main is used to control the state of the server at the highest level
//currently it initialises the perudo code in a separate thread and then waits for a quit command
int main()
{
	//seed the dice (may as well do it here)
	unsigned int seed=std::chrono::system_clock::now().time_since_epoch().count();
	Die::seed(seed);
	
	//perudo thread (currently detched making its task embarrasingly parallel)
	std::thread perudo_thread(perudo);
	perudo_thread.detach();
	
	//loop until a "q" character is entered
	char input;
	do
	{
		std::cin>>input;
	}
	while(input!='q');
	
	return 0;
}


//perudo proccessing function
//contains the main body of perudo playing code
void perudo()
{
	//empty wheel of players
	wheel<Player*> players;
	
	//list of all the bids in the game
	std::list<Bid*> bids;
	//the bid of the next player
	Bid* next_bid=nullptr;
	
	//variable for totalling the dice counts during a challenge
	unsigned int total=0;
	
	//the client manager
	clientManager client_manager(8000);
	
	//MAIN LOOP
	//---------------------------------------------------------------------------------------------------------------------------
	while(true)
	{
		//PRE-GAME SETUP
		//-----------------------------------------------------(((
		//create the players
		client_manager.populate(players);
		
		//roll the dice
		for(unsigned int i=0;i<players.size();++i)
		{
			players[i]->roll();
		}
		
		//current player iterator
		wheel<Player*>::iterator player_it=players.begin();
		//-----------------------------------------------------)))
		
		
		
		//GAME LOOP
		//--------------------------------------------------------------------******(((
		while(players.size()>1)
		{
			//STANDARD TURN ACTIONS
			//-----------------------------------------------------(((
			//tell the next player to take their turn
			next_bid=(*player_it) -> takeTurn( bids.back() );
			
			//broadcast the bid
			for(unsigned int i=0;i<players.size();++i)
			{
				players[i]->sendBid(next_bid);
			}
			//-----------------------------------------------------)))
			
			
			
			//BID CODE
			//-----------------------------------------------------(((
			//if a bid was made, store it and move on to the next player's turn
			if(next_bid)
			{
				bids.push_back(next_bid);
			}
			//-----------------------------------------------------)))
			
			
			
			//CHALLENGE CODE
			//-----------------------------------------------------(((
			//if no bid was made then a challenge has been levelled...
			else
			{
				//total the dice of the appropiate number
				total=0;
				for(unsigned int j=0 ; j<players.size() ; ++j)
				{
					//add the number of each appropriate die owned by the players to the total
					total+=players[j] -> countDice( bids.back() -> second);
				}
				
				
				//check who won
				wheel<Player*>::iterator loser=players.begin();
				if( bids.back() -> second <= total )loser=player_it;
				else loser=player_it-1;
				
				//punish the loser
				if( !(*loser) -> removeDice())
				{
					delete *loser;
					players.erase(loser);
				}
				
				//once the challenge is completed, re-roll the dice in preparation for the next round
				for(unsigned int i=0;i<players.size();++i)
				{
					players[i]->roll();
				}
			}
			//-----------------------------------------------------)))
		}
		//--------------------------------------------------------------------******)))
		
		
		
		//POST GAME CLEAN-UP
		//-----------------------------------------------------(((
		
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
		//-----------------------------------------------------)))
		
		//basic throttling to reduce overheating/processor-hogging
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	//---------------------------------------------------------------------------------------------------------------------------
}