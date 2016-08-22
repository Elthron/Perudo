#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <utility>
#include <iostream>

class client{

   int filedes;
   char buffer[256];
public:

   client(int connection);
   std::pair<int,int> takeTurn(char play[2]);
};

int main( int argc, char *argv[] ) {

//set up the socket
   int sockfd, newsockfd, portno;
   unsigned int clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   //int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
///////////////////////////////////////////////////////////////////////////////
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
      //error handling
   }  
///////////////////////////////////////////////////////////////////////////////

   client frodo(newsockfd);
   char foo[3] = {'1','2','\0'};
   while(1){
      std::pair<int,int> bar = frodo.takeTurn(foo);
      std::cout<< "the play was: " << bar.first <<"\t"<<bar.second<<"'s\n";
   }
   return 0;
}

client::client(int connection){
   filedes = connection;
   bzero(buffer,256);
}

std::pair<int,int> client::takeTurn(char play[]){
   //the length of 2 ints
   //writes previous play to socket
   //needs to check if client still there
   const void *buf = play;
   write(filedes,buf,sizeof(buf));
   //reads the play 
   bzero(buffer,256);//clears the buffer
   read(filedes,buffer, 255);
   
   int i = buffer[0] - '0';
   int j = buffer[1] - '0';

   std::pair<int,int> bluf;
   bluf.first = i;
   bluf.second = j;

   return bluf;
}
