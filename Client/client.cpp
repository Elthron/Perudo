//client Stuff
//commented out all std::cout, it will mess up ncurses
#include <iostream>
#include "client.h"
#include "player.h"

client::client(std::vector<player*>* p, self* me):pplayerVector(p),pself(me){
}

int client::connectToServer(int port, char *host[], std::string name){
	//returns 0 on success
	portno = port;
	server = gethostbyname(*host);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		std::cout<<"Error: failed to open socket"<<std::endl;
		return 1;
	}
	if(server == NULL){
		std::cout<<"Error: no such host"<<std::endl;
		return 2;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
   	serv_addr.sin_family = AF_INET;
  	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   	serv_addr.sin_port = htons(portno);

   	   	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    	std::cout<<"Error: failed to connect to server"<<std::endl;
      	return 3;
   	}

   	std::cout<<"connected to server"<<std::endl;
   	bzero(recbuf,sizeof(recbuf));
   	strcpy(&recbuf[0] , name.c_str());
   	//send your name to the server
   	int n = send(sockfd,name.c_str(),sizeof(recbuf),0);
   	return 0;

}

bool client::getServerData(){
	bzero(buffer,256);
	//blocking function
	n = recv(sockfd, buffer, sizeof(buffer),0); //first byte tells us the message type;
		
	if(n < 0){
		return false;
	}
	///////////message info
	std::cout<<"raw message (char): ";
	for(int i = 0; i < 255; ++i){
		std::cout<<(char) buffer[i];
	}
	std::cout<<std::endl<<"message type: "<< static_cast<int> (buffer[0]) <<std::endl;
	std::cout<<"bytes recieved: "<<n<<std::endl;
	///////////
	//message recieved from the server in char form


	switch(buffer[0]){

		case 1:
			return this->updatePlayerBid();
		case 2:
			return this->Reroll();
		case 3:
			return this->updatePlayerDieNumber();
		case 4:
			return this->makeBid();
		case 5:
			return this->updatePlayerNames();
		default:
			return false;
	}

}

bool client::updatePlayerNames(){
	
	std::vector<std::string> names;

	char *start = (char*) &buffer[2];
	std::string allNames (start);
	//std::cout<<"all names: "<<allNames<<std::endl;

	//In order to avoid O(2) algorithm, we are going to wipe the player list
	//and start again

	for(auto iter=pplayerVector->begin(),end=pplayerVector->end(); iter != end; ++iter){
		if(*iter != pself){
			delete *iter;
			pplayerVector->erase(iter);
		}
	}

	char * p;
	/*
	this really cool for loop takes the long string (allNames) recieved by the client
	and it iterates backwards over it. when it hits char 255 it makes a new string 
	with the pointer to that location. it replaces char 255 with a null terminator
	and carries on going backwards. then it creates a new player with that name.
	*/
	allNames.pop_back();
	for(auto it = allNames.rbegin();it != allNames.rend(); ++it ){
		if(*it == (char) 255 && it !=allNames.rbegin()){
			p = &(*(it-1));//-1 to get rid of char 255
			std::string temp(p);
			//std::cout<<"name: "<<temp<<std::endl;
			*it = '\0';

			//checks if the name is YOUR name and put your pointer on the back
			if(temp == pself->getName()){
				pplayerVector->push_back(pself);
			}
			else{
				opponent *op = new opponent(5);
				op->setName(temp);
				pplayerVector->push_back(op);
			}	

		}
		if(it == allNames.rend()-1){
			p = &(*(it));
			std::string temp(p);
			//std::cout<<"name: "<<temp<<std::endl;
			names.push_back(temp);
			*it = '\0';		
			
			if(temp == pself->getName()){
				pplayerVector->push_back(pself);
			}
			else{
				opponent * op = new opponent(5);
				op->setName(temp);
				pplayerVector->push_back(op);
			}
		}	
	}

	return true;
	
}

bool client::updatePlayerBid(){
	std::cout<<"updatePlayerBid"<<std::endl;

	int numberOfDice = static_cast<int> (buffer[1]);
	int valueOfDice = static_cast<int> (buffer[2]);
	char *start = (char*) &buffer[3];
	std::string playerName (start);
	std::cout<<"player name: "<< playerName <<"\t bid: "<< numberOfDice << " " << valueOfDice<<std::endl;

	for (auto iter = pplayerVector->begin(); iter != pplayerVector->end();++iter){
		if((*iter)->getName() == playerName){
			(*iter)->setBid(Bid(numberOfDice,valueOfDice));
		}
	}

	return true;
}

bool client::Reroll(){
	int numberOfDice = static_cast<int> (buffer[1]);
	
	std::vector<int> dice;

	for(int i = 0; i < numberOfDice; ++i){
		dice.push_back(static_cast<int> (buffer[2+i])); //2nd position is the start of the dice info
	}
	pself->setDice(dice);
	return true;
}

bool client::updatePlayerDieNumber(){
	std::string player((char*) &buffer[1]); //doesnt work with static cast...?
	std::cout<<"removing a dice from "<<player<<std::endl;
	for(auto iter = pplayerVector->begin(); iter != pplayerVector->end(); ++iter){
		if((*iter)->getName() == player){
			(*iter)->removeDie(); //holy shit that worked
		}
	}

	return true;	
}


bool client::makeBid(){
	int numberOfDice,valueOfDice;
	std::cout<<"enter the number of Dice you want to play: ";
	std::cin>>numberOfDice;
	std::cout<<"enter the value of Dice you want to play: ";
	std::cin>>valueOfDice;

	bzero(recbuf,sizeof(recbuf));
   	buffer[0]= (char) numberOfDice;
   	buffer[1]= (char) valueOfDice;

   	//send your name to the server
   	int n = send(sockfd,buffer,2,0);

	return true;
}

void client::testFunc(){
	//std::cout<<mess<<std::endl;
	std::cout<<pplayerVector->size()<<std::endl;
	for(auto iter = pplayerVector->begin(); iter!=pplayerVector->end(); ++iter){
		std::cout<<(*iter)->getName();
	}
}