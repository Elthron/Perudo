#include "AI.h"

AI::AI(unsigned int die_size, std::string _name):
	Player(die_size, name)
{}

void AI:notify(Message& message)
{
	//call the appropriate function corresponding to the message id
	switch(message.id)
	{
		case 1:
			recievePlayerList(message.players_vec);
			break;
		case 2:
			recieveNewBid(message.dice_number_,message.number_of_dice_, message.relevant_player);
			break;
		case 3:
			recieveDiceRoll(message.roll_values);
			break;
		case 4:
			recieveDiceLoss(message.relevant_player);
			break;
		default:
			//bid instruction messages do not need to be handled by AIs
			return;
	}
}