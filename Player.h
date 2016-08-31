#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>
#include "Die.h"
#include "Bid.h"

//abstract base class to descend humans and AIs form
class Player
{
	public:
		Player(unsigned int die_size);
		virtual ~Player();
		
		//function to ask the client to take their turn based on the last bid
		virtual Bid* takeTurn(Bid* last_bid)=0;
		//function to inform the player of other bids
		virtual void sendBid(Bid* bid)=0;
		
		//function to roll the player's dice
		virtual void roll();
		//function to remove a dice from the player; returns false if there are no dice left after this
		virtual bool removeDice();
		//function used when a player has been challenged to return the number of dice a player has that show the given value
		virtual unsigned int countDice(unsigned int value);
		
	private:
		//the player's dice
		std::vector<Die> dice;
};

#endif
