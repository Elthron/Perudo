#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>
#include "Die.h"
#include "Bid.h

//abstract base class to inherit humans and AIs from
class Player
{
	public:
		Player(unsigned int die_size);
		
		virtual Bid* takeTurn(Bid last_bid)=0;
		virtual void sendBid(Bid bid)=0;
		virtual bool removeDice();
		virtual unsigned int countDice(unsigned int number) const;
		
	private:
		std::vector<Die> Dice;
};

#endif
