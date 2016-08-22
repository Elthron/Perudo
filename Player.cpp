#include "Player.h"

Player::Player(int _client_id,unsigned int die_size):
	client_id(_client_id),
	dice( 5, Die(dice_size) )
{}

Bid Player::takeTurn(Bid last_bid)
{}

void Player::sendBid(Bid bid)
{}

bool removeDice()
{
	dice.erase(dice.end()-1);
	return dice.size();
}

unsigned int countDice(unsigned int value) const
{
	unsigned int count=0;
	
	for(auto iter=dice.begin(),end=dice.end() ; iter!=end ; ++iter)
	{
		if( (*iter).getValue()==value)++count;
	}
	
	return count;
}
