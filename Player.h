#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <utility>
#include "Die.h"
#include "Bid.h"

//abstract base class to descend humans and AIs form
class Player
{
	public:
		//c/dtor
		Player(unsigned int die_size, std::string _name);
		virtual ~Player();
		
		//function to ask the client to take their turn based on the last bid
		virtual Bid* takeTurn()=0;
		
		//function to roll the player's dice
		virtual void roll();
		//function to remove a dice from the player; returns false if there are no dice left after this
		virtual bool removeDice();
		//function used when a player has been challenged to return the number of dice a player has that show the given value
		virtual unsigned int countDice(unsigned int value);
		
		std::string getName();
		
	protected:
		//the player's dice
		std::vector<Die> dice;
		//the player's identification
		std::string name;
};

#endif
