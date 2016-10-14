#include "player.h"
#include <iostream>

player::~player(){}

void player::setBid(Bid b){
	bid = b;
}

Bid player::getBid(){
	return bid;
}

int player::getNumberOfDice(){
//fixes vtable
}

void player::setName(std::string s){
	name = s;
}

std::string player::getName(){
	return name;
}

void player::removeDie(){
	std::cout<<"aww fiuckkk"<<std::endl;
}

////////////////////////////////////////////////////////////
self::self(std::vector<int> v): dice(v){

}

int self::getNumberOfDice(){
	return dice.size();
}

std::vector<int> self::getDice(){
	return dice;
}

void self::setDice(std::vector<int> d){
	dice = d;
}
////////////////////////////////////////////////////////////

opponent::opponent(int n):numberOfDice(n){

}

int opponent::getNumberOfDice(){
	return numberOfDice;
}

void opponent::removeDie(){
	numberOfDice -=1;
}