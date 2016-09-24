#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>

class Message
{
	public:
		Message();
		~Message();
		//deny copying and assignment
		Message(const Message& m)=delete;
		Message& operator=(const Message& m)=delete;
		
		void storePlayerList(std::vector<std::string> players);
		void storeNewBid(int dice_number, int number_of_dice, std::string player);
		void storeDiceRoll(std::vector<int> values);
		void storeLoseDice(std::string player);
		void storeBidInstruction();
		
		void* getMessage();
		size_t getSize();
		
	private:
		void* message;
		size_t size;
};

void storeInt(unsigned char* target, const int& value);
void storeString(unsigned char* target, const std::string& value);

ostream& operator<<(ostream& os, const Message& m);

#endif
