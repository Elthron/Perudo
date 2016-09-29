#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>
#include <string>

class ostream;

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
		friend std::ostream& operator<<(std::ostream& os, const Message& m);
		
		//message components for use by the AI object
		//there is literally no point in these being private
		//I know you're not supposed to do this because you might change your mind/can't predict future design decisions
		//but I'm such an incredible genius that this will never happen to me
		//therefore I will stand by this decision until it comes crashing down around my ears
		//(and then never do this again)
		unsigned int id;
		std::vector<std::string> players_vec;
		unsigned int dice_number_;
		unsigned int number_of_dice_;
		std::vector<int> roll_values;
		std::string relevant_player;
		
	private:
		unsigned char* message;
		size_t size;
};

void storeInt(unsigned char*& target, const int& value);
void storeString(unsigned char*& target, const std::string& value);


#endif
