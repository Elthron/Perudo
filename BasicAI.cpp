#include "BasicAI.h"

BasicAI(unsigned int _dice_size,std::vector<Bid*>& _bids):
	Player(_dice_size),
	bids(_bids)
{}

Bid* takeTurn(Bid last_bid)
{
	//calculate highest value bid that can be made
	
	//if current bid is lower, bid it
	
	//else challenge
}

void sendBid(Bid bid)
{}
