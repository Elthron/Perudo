#include "client.h"
#include <stdlib.h>
#include <iostream>

int main(int, char * argv[]){
	client frodo;
	int portno = atoi(argv[1]);
	frodo.connectToServer(portno,&argv[2]);
	frodo.getServerData();
	frodo.getServerData();
	frodo.getServerData();
	frodo.getServerData();
	
	return 0;
}