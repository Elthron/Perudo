#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>
#include "Die.h"

//in this game a "bid" is a std::pair of ints: 4 2s -> std::pair<unsigned int,unsigned int> {4,2}
typedef std::pair<unsigned int,unsigned int> Bid;

//abstract base class to inherit humans and AIs from
class Player
{
	public:
		Player(int _client_id,unsigned int die_size);
		
		virtual Bid takeTurn(Bid last_bid)=0;
		virtual void sendBid(Bid bid)=0;
		bool removeDice();
		unsigned int countDice(unsigned int number) const;
		
	private:
		int client_id;
		std::vector<Die> Dice;
};

#endif
