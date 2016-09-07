#ifndef BASICAI_H
#define BASICAI_H

#include <list>
#include "Player.h"

class BasicAI : public Player
{
	public:
		explicit BasicAI(unsigned int _dice_size,std::list<Bid*>& _bids,unsigned int _total_dice);
		
		//function to ask the client to take their turn based on the last bid
		virtual Bid* takeTurn(Bid* last_bid);
		//function to inform the player of other bids
		virtual void sendBid(Bid*);
		//function used when a player has been challenged to return the number of dice a player has that show the given value
		virtual unsigned int countDice(unsigned int value);
		
	private:
		std::list<Bid*>& bids;
		unsigned int total_dice;
};

#endif
