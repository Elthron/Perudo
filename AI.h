#ifndef AI_H
#define AI_H

#include <string>
#include "Player.h"

class Message;

class AI : public Player
{
	public:
		explicit AI(unsigned int die_size, std::string _name);
		
		//the following function calls the private function which corresponds to the calling message object
		final virtual void notify(Message& message);
	
	private:
		//these functions are given no behavior by default and are there to be overridden by AIs that want to handle the information in some way
		virtual void recievePlayerList(std::vector<std::string> players){}
		virtual void recieveNewBid(int dice_number, int number_of_dice, std::string player){}
		virtual void recieveDiceRoll(std::vector<int> values){}
		virtual void recieveDiceLoss(std::string player){}
}

#endif