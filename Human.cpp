#include <string>
#include "clientManager.h"
#include "Message.h"
#include "Human.h"

clientManager* Human::mgr;

Human::Human(int _client_id):
	Player(6,"Bob"),
	client_id(_client_id)
{}

Bid* Human::takeTurn()
{
	//make the message
	Message message;
	message.storeBidInstruction();
	
	//send the message
	mgr->whisper(message,client_id);
	
	std::string response=mgr->getResponse(client_id);
	
	return new Bid((unsigned int)response[1],(unsigned int)response[2]); //this probably doesn't work
}

void Human::notify(Message& message)
{
	mgr->whisper(message,client_id);
}

void Human::roll()
{
	std::vector<int> values;
	
	//iteratively roll the dice and store the values
	for(unsigned int i=0 ; i<dice.size() ; ++i)
	{
		dice[i].roll();
		values.push_back(dice[i].getValue());
	}
	
	//make a message
	Message message;
	message.storeDiceRoll(values);
	
	//send the message
	mgr->whisper(message,client_id);
}

void Human::setMgr(clientManager* _mgr)
{
	mgr=_mgr;
}