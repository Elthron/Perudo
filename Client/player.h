#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Bid.h"

class player{

	private:
		Bid bid;
		std::string name;

	public:
		virtual int getNumberOfDice() = 0;
		virtual void removeDie();
		virtual ~player();
		
		Bid getBid();
		void setBid(Bid b);
		void setName(std::string s);
		std::string getName();

};

class self: public player { //not sure what the appropriate specifier is here

	private:	
		std::vector<int> dice;

	public:
		self(std::vector<int> v);
		virtual int getNumberOfDice();
		std::vector<int> getDice();
		void setDice(std::vector<int>);
};

class opponent: public player{
	
	private:
		int numberOfDice;

	public:
		opponent(int n);
		virtual int getNumberOfDice();
		virtual void removeDie();

};


#endif