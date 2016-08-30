#include "Player.h"

Player::Player(unsigned int die_size):
	dice( 5, Die(die_size) )
{}

Player::~Player()
{}

bool Player::removeDice()
{
	dice.erase(dice.end()-1);
	return dice.size();
}

unsigned int Player::countDice(unsigned int value)
{
	unsigned int count=0;
	
	for(auto iter=dice.begin(),end=dice.end() ; iter!=end ; ++iter)
	{
		if( (*iter).getValue()==value)++count;
	}
	
	return count;
}
