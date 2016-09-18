#include "client.h"
#include <stdlib.h>
#include <iostream>

int main(int argc, char *argv[]){

	if(argc != 3){
		std::cout<<"Usage: <port> <host>"<<std::endl;
		return 1;
	}
	client joe;
	int portno = atoi(argv[1]);
	joe.connectToServer(portno,&argv[2]);
	joe.getServerData();

	return 0;
}