#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <utility>
#include "Die.h"

typedef std::pair<unsigned int,unsigned int> Bid;

class Player
{
	public:
		Player(int _client_id,unsigned int die_size);
		
		Bid takeTurn(Bid last_bid);
		void sendBid(Bid bid);
		bool removeDice();
		unsigned int countDice(unsigned int number) const;
		
	private:
		int client_id;
		std::vector<Die> Dice;
};

#endif
