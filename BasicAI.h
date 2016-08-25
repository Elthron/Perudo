#ifndef BASICAI_H
#define BASICAI_H

#include "Player.h"

class BasicAI : public Player
{
	public:
		explicit BasicAI(unsigned int _dice_size,std::vector<Bid*>& _bids);	//Bid type is defined in player class
		
		//function to ask the client to take their turn based on the last bid
		Bid takeTurn(Bid last_bid)=0;
		//function to inform the player of other bids
		void sendBid(Bid bid)=0;
		
	private:
		std::vector<Bid*>& bids;
};

#endif
