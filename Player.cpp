#include "Player.h"

Player::Player(unsigned int die_size):
	dice( 5, Die(dice_size) )
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
