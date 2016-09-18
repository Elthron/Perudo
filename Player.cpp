#include "Player.h"

Player::Player(unsigned int die_size, std::string _name):
	dice( 5, Die(die_size) ),
	name(_name)
{}

Player::~Player()
{}

void Player::roll()
{
	//iteratively roll the dice
	for(unsigned int i=0 ; i<dice.size() ; ++i)
	{
		dice[i].roll();
	}
}

bool Player::removeDice()
{
	dice.erase(dice.end()-1);
	return dice.size();
}

unsigned int Player::countDice(unsigned int value)
{
	//tally variable
	unsigned int count=0;
	
	//tally the dice with the correct values
	for(auto iter=dice.begin(),end=dice.end() ; iter!=end ; ++iter)
	{
		if( (*iter).getValue()==value)++count;
	}
	
	return count;
}

std::string Player::getName()
{
	return name;
}