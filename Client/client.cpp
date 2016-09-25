//client Stuff
//commented out all std::cout, it will mess up ncurses
#include "client.h"
client::client():numberOfPlayers(1){
}

int client::connectToServer(int port, char *host[]){
	//returns 0 on success
	portno = port;
	server = gethostbyname(*host);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		//std::cout<<"Error: failed to open socket"<<std::endl;
		return 1;
	}
	if(server == NULL){
		//std::cout<<"Error: no such host"<<std::endl;
		return 2;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
   	serv_addr.sin_family = AF_INET;
  	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   	serv_addr.sin_port = htons(portno);

   	   	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    	//std::cout<<"Error: failed to connect to server"<<std::endl;
      	return 3;
   	}

   	//std::cout<<"connected to server"<<std::endl;
   	return 0;

}

bool client::getServerData(){
	bzero(buffer,256);
	//blocking function
	n = recv(sockfd, buffer, sizeof(buffer),0); //first byte tells us the message type;
		
	if(n < 0){
		return false;
	}
	//std::cout<<"bytes recieved"<<n<<std::endl;
	//std::cout<<"message type: "<< static_cast<int> (buffer[0]) <<std::endl;

	switch(buffer[0]){

		case 5:
			return this->updatePlayerNames();
		case 1:
			return this->updatePlayerBid();
		case 2:
			return this->Reroll();
		case 3:
			return this->updatePlayerDieNumber();
		case 4:
			return this->makeBid();
		default:
			return false;
	}

}

bool client::updatePlayerNames(){
	//std::cout<<"updatingPlayerNames"<<std::endl;
	//get number of players
	/*OMG this fucking piece of shit, it wouldnt compile without
	* -std=c++14 wtf am I on the cutting edge of oo programming?*/
	numberOfPlayers = static_cast<int> (buffer[1]); 

	char *start = (char*) &buffer[2];
	std::string allNames (start);
	//std::cout<<"number of players: "<< numberOfPlayers<<std::endl
	//<<"all names "<< allNames << std::endl;
	
	//make the char buffer into a string so I can use string methods
	
	/*now for the assumptions:
	* -all names are 8 characters
	* -none of the characters are '\0'
	*/
	
	//adds players
	for (int i = 0; i < numberOfPlayers; ++i){
		playerInfo temp;
		temp.name = allNames.substr(i*8,8);
		players.push_back(temp);
	}
	//prints player names
	//std::cout<<"players: "<<std::endl;
	std::vector<playerInfo>::iterator it;
	for (it = players.begin(); it != players.end(); ++it){
		//std::cout<<it->name<<std::endl;
	}
	
	return true;
}

bool client::updatePlayerBid(){
	//std::cout<<"updatePlayerBid"<<std::endl;

	int numberOfDice = static_cast<int> (buffer[1]);
	int valueOfDice = static_cast<int> (buffer[2]);
	char *start = (char*) &buffer[3];
	std::string playerName (start);

	/*look through player list to update correct piece of info*/
	//std::cout<<playerName<<std::endl;
	std::vector<playerInfo>::iterator it;	
	for (it = players.begin(); it != players.end(); ++it){
		/*if the playeName matches the name of one 
		of the playerInfo structs, change tuhe bid*/
		if(playerName == it->name){
			it->bid.first = numberOfDice;
			it->bid.second = valueOfDice;
			
			//std::cout<<"number of Dice:"<<
			//it->bid.first <<". Value of Dice: "<<
			//it->bid.second<<std::endl;
		}
	}	
	return true;
}

bool client::Reroll(){
	//std::cout<<"Reroll"<<std::endl;
	dice.clear();
	numberOfDice = static_cast<int>(buffer[1]);
	for (int i = 0; i < numberOfDice ;++i){
		dice.push_back(static_cast<int>(buffer[i+2]));
	}
	std::vector<int>::iterator it;
	for(it = dice.begin(); it != dice.end(); ++it){
		//std::cout<<*it<<std::endl;
	}
	return true;
}

//this removes a dice
bool client::updatePlayerDieNumber(){
	//std::cout<<"updatePlayerDieNumber"<<std::endl;
	char *start = (char*) &buffer[1];
	std::string playerName (start);
	
	std::vector<playerInfo>::iterator it;	
	for (it = players.begin(); it != players.end(); ++it){
		/*if the playeName matches the name of one 
		of the playerInfo structs, change tuhe bid*/
		if(playerName == it->name){
			it->numberOfDice =-1;
		}
	}	
	return true;
}


bool client::makeBid(){
	//std::cout<<"makeBid"<<std::endl;
	//some sort of make bid thing
	return true;
}


std::vector<playerInfo> client::getPlayerInfo(){
	return players;
}

playerInfo client::getPlayerInfo(int i){
	return players[i];
}