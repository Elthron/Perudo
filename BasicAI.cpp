#include <cmath>
#include "BasicAI.h"

BasicAI::BasicAI(unsigned int _dice_size,std::list<Bid*>& _bids,unsigned int _total_dice):
	Player(_dice_size),
	bids(_bids),
	total_dice(_total_dice)
{}

Bid* BasicAI::takeTurn(Bid* last_bid)
{
	//create the highest likely bid
	Bid* new_bid=new Bid( std::floor(total_dice/6) ,1);
	
	if(*new_bid>*last_bid)return new_bid;
	else return nullptr;
}

void BasicAI::sendBid(Bid*)
{}

unsigned int BasicAI::countDice(unsigned int value)
{
	--total_dice;
	return Player::countDice(value);
}
