#include <iostream>
#include "player.h"

int main(){

	std::vector<player*> players;
	std::vector<int> x = {1,2,3,4,5};

	self p1(x);
	opponent p2(2);
	opponent p3(4);

	player * pp1 = &p1;
	player * pp2 = &p2;
	player * pp3 = &p3;	

	pp1->setName("frodo");
	pp2->setName("Bob Ross");
	pp3->setName("memeMan");


	players.push_back(pp1);
	players.push_back(pp2);
	players.push_back(pp3);


	std::vector<player*>::iterator it;
	int i = 0;
	for(it = players.begin(); it !=players.end(); ++it, ++i){
		(*it)->setBid({1+i,2+i});
		if(*it == pp1){
			std::cout<<"You have "<<(*it)->getNumberOfDice()<<" dice."<<std::endl;
			std::cout<<"Your bid "<<(*it)->getBid().first<<" "<<(*it)->getBid().second<<std::endl;
		}
		else{
			std::cout<<"Opponent has "<< (*it)->getNumberOfDice()<< " dice."<<std::endl;
			std::cout<<"Opponent bid "<<(*it)->getBid().first<<" "<<(*it)->getBid().second<<std::endl;
		}
	}

	return 0;
}