#include <cstdlib>
#include "Message.h"
#include <iostream>

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
	//make sure the message is blank
	if(message) free(message);
	
	//find out the total size of all the strings
	int strings_size=0;
	for(unsigned int i=0 ; i<players.length() ; ++i)
	{
		strings_size+=players[i].size()+1;	//+1 to include null terminator
	}
	
	size=3+strings_size;
	message=calloc(size, sizeof(char));
	
	//get memory pointer
	unsigned char* mem=static_cast<unsigned char*>(message);
	
	//add prepend
	storeInt(mem,5);
	
	//add number of players
	storeInt(mem,players.size());
	
	//add each of the strings
	
	//make a temmporary string which is all the strings in the list combined
	std::string temp;
	for(auto iter=players.begin(),end=players.end() ; iter!=end ; ++iter)
	{
		//replace the null terminator with a new line character
	/*
		nothing I do fixes this, im not sure you can actually change the null terminator
		at the end of string, I think we might need to store all this in a char array 
		std::string temp = *iter;
		temp[temp.length()] = '\n';
	*/
		*iter += static_cast<char> (255);//put an unlikely-to-be-used character at the end
		temp += *iter;
	}
	storeString(mem,temp);
	//null terminate the message
	*mem=0;
}

void Message::storeNewBid(int dice_number, int number_of_dice, std::string player)
{
	//make sure the message is blank
	if(message) free(message);
	
	size=6+player.size();
	message=calloc(size,sizeof(char));
	
	//get memory pointer
	unsigned char* mem=static_cast<unsigned char*>(message);
	
	//add prepend
	storeInt(mem,1);
	
	//store data
	storeInt(mem,dice_number);
	storeInt(mem,number_of_dice);
	storeString(mem,player);
	
	//null terminate the message
	*mem=0;
}

void Message::storeDiceRoll(std::vector<int> values)
{
	//make sure the message is blank
	if(message) free(message);
	
	size=2+values.size();	//2 for prepend+append
	message=calloc(size,sizeof(char));
	
	//get memory pointer
	unsigned char* mem=static_cast<unsigned char*>(message);
	
	//add prepend
	storeInt(mem,2);
	
	//store data
	storeInt(mem,values.size());
	
	for(unsigned int i=0 ; i<5 ; ++i) //maximum of 5 dice values sent
	{
		if( i <= values.size() ) storeInt(mem,values[i]);
	}
	
	//null terminate the message
	*mem=0;
}

void Message::storeLoseDice(std::string player)
{
	//make sure the message is blank
	if(message) free(message);
	
	size=3+player.size;
	message=calloc(size,sizeof(char));
	
	//get memory pointer
	unsigned char* mem=static_cast<unsigned char*>(message);
	
	//add prepend
	storeInt(mem,3);
	
	//store data
	storeString(mem,player);
	
	//null terminate the message
	*mem=0;
}

void Message::storeBidInstruction()
{
	//make sure the message is blank
	if(message) free(message);
	
	size=2;
	message=calloc(size,sizeof(char));
	
	//get memory pointer
	unsigned char* mem=static_cast<unsigned char*>(message);
	
	//add prepend
	storeInt(mem,4);
	
	//null terminate the message
	*mem=0;
}

void* Message::getMessage(){return message;}
size_t Message::getSize(){return size;}

void storeInt(unsigned char* target, const int& value)
{
	//store the int (this causes truncation if the int is more than 15)
	*target=value;
	
	//increment memory for consistency with other function
	++target;
}

void storeString(unsigned char* target, const std::string& string)
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
	
	for(char* iter = static_cast<char*> (m.message); *iter ; ++iter){	
		os<<*iter;
	}
	return os;
}