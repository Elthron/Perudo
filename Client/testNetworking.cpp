/*
g++ client.h client.cpp player.h player.cpp testNetworking.cpp -o testNetworking -std=c++14
*/

#include "client.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>

void printPlayerInformation(std::vector<player*>* p, self * p1);

int main(int argc, char *argv[]){
/*test data*/

	std::vector<player*> players;
	std::vector<int> x = {1,2,3,4,5};

	self p1(x);

	//player * pp1 = &p1;

	if(argc != 3){
		std::cout<<"Usage: <port> <host>"<<std::endl;
		return 1;
	}
	int portno = atoi(argv[1]);

	std::string name;
	std::cout<<"Enter your name: ";
	std::cin>>name;

	p1.setName(name);

	client frodo(&players,&p1);
	frodo.connectToServer(portno,&argv[2],p1.getName());
	
	frodo.getServerData(); //tests player list update
	printPlayerInformation(&players, &p1);

	frodo.getServerData();  //tests update bid 
	printPlayerInformation(&players, &p1);

	frodo.getServerData();  //tests reroll 
	printPlayerInformation(&players, &p1);

	frodo.getServerData();  //tests remove die 
	printPlayerInformation(&players, &p1);

	frodo.getServerData();  //tests make bid
	
	frodo.getServerData();  //tests update bid 
	printPlayerInformation(&players, &p1);


	return 0;
}

void printPlayerInformation(std::vector<player*>* p,self * p1){
	std::cout<<std::endl;
	std::cout<<std::setw(16)<<"Player Name"<<std::setw(6)<<"Bid"
	<<"\t Number of Dice"<<std::endl;
	for(auto iter = p->begin(); iter != p->end(); ++iter){
		std::cout<<std::setw(16)<< (*iter)->getName()<<std::setw(6)
		<< (*iter)->getBid().first << ' '<< (*iter)->getBid().second <<'\t'
		<< (*iter)->getNumberOfDice() << std::endl;
	}
	std::vector<int> dice(p1->getDice());
	std::cout<<"your Dice: ";
	for(auto iter = dice.begin(); iter != dice.end(); ++iter){
		std::cout<<*iter<<" ";
	}
	std::cout<<std::endl;
	std::cout<<std::endl;
}