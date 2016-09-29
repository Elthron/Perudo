#include <cstdlib>
#include <iostream>
#include "Message.h"

Message::Message():
	message(nullptr),
	size(0)
{}

Message::~Message()
{
	//only free the message memory if it has been assigned
	if(message)	free(message);
}

void Message::storePlayerList(std::vector<std::string> players)
{
	//set the AI components
	id=5;
	players_vec=players;
	
	//make sure the message is blank
	if(message) free(message);
	
	//find out the total size of all the strings
	int strings_size=0;
	for(unsigned int i=0 ; i<players.size() ; ++i)
	{
		strings_size+=players[i].size()+1;	//+1 to include null terminator
	}
	
	size=3+strings_size;
	message=static_cast<unsigned char*> (calloc(size, sizeof(unsigned char)));
	unsigned char* message_temp=message;
	
	//add prepend
	storeInt(message_temp,-1);
	
	//add number of players
	storeInt(message_temp,players.size());
	
	//add each of the strings
	for(unsigned int i=0 ; i<players.size() ; ++i)
	{
		storeString(message_temp,players[i]);
	}
}

void Message::storeNewBid(int dice_number, int number_of_dice, std::string player)
{
	//set the AI components
	id=1;
	dice_number=dice_number_;
	number_of_dice=number_of_dice_;
	relevant_player=player;
	
	//make sure the message is blank
	if(message) free(message);
	
	size=6+player.size();
	message=static_cast<unsigned char*> (calloc(size,sizeof(char)));
	unsigned char* message_temp=message;
	
	//add prepend
	storeInt(message_temp,1);
	
	//store data
	storeInt(message_temp,dice_number);
	storeInt(message_temp,number_of_dice);
	storeString(message_temp,player);
}

void Message::storeDiceRoll(std::vector<int> values)
{
	//set the AI components
	id=2;
	roll_values=values;
	
	//make sure the message is blank
	if(message) free(message);
	
	size=2+values.size();	//2 for prepend+append
	message=static_cast<unsigned char*> (calloc(size,sizeof(char)));
	unsigned char* message_temp=message;
	
	//add prepend
	storeInt(message_temp,2);
	
	//store data
	storeInt(message_temp,values.size());
	
	for(unsigned int i=0 ; i<5 ; ++i) //maximum of 5 dice values sent
	{
		if( i <= values.size() ) storeInt(message_temp,values[i]);
	}
}

void Message::storeLoseDice(std::string player)
{
	//set the AI components
	id=3;
	relevant_player=player;
	
	//make sure the message is blank
	if(message) free(message);
	
	size=3+player.size();
	message=static_cast<unsigned char*> (calloc(size,sizeof(char)));
	unsigned char* message_temp=message;
	
	//add prepend
	storeInt(message_temp,3);
	
	//store data
	storeString(message_temp,player);
}

void Message::storeBidInstruction()
{
	//set the AI components
	id=4;
	
	//make sure the message is blank
	if(message) free(message);
	
	size=2;
	message=static_cast<unsigned char*> (calloc(size,sizeof(char)));
	unsigned char* message_temp=message;
	
	//add prepend
	storeInt(message_temp,4);
}

void* Message::getMessage(){return static_cast<void*>(message);}
size_t Message::getSize(){return size;}

void storeInt(unsigned char*& target, const int& value)
{
	//cast value to a char
	const unsigned char& _value=static_cast<const unsigned char&> (value);
	
	//store the int (this causes truncation if the int is more than 15)
	*target=_value;
	
	//increment memory for consistency with other function
	++target;
}

void storeString(unsigned char*& target, const std::string& string)
{
	
	//add the string to the message
	for(unsigned int i=0 ; i<string.length() ; ++i)
	{
		*target=string[i];
		++target;
	}
	
	//terminate the string
	*target=255;
	++target;
}

std::ostream& operator<<(std::ostream& os, const Message& m){
	os<<"message size="<<m.size<<std::endl;
	os<<"message content=";
	
	unsigned char* ptr=m.message;
	
	os<<*((int*)ptr)<<" ";
	++ptr;
	
	while(*ptr){
		os<<*ptr<<" ";
		++ptr;
	}
	os<<std::endl;

	return os;
}