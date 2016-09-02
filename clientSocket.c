//this is the god awful client program. to use it with
//networking test, compile it with g++ clientSocket.c -o client -Wall -Werror -Wextra
//and run ./client 127.0.0.1 5001

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>


int main(int argc, char *argv[]) {
   //at some point I wrote all this stuff, I have forgotten how
   // a lot of it works/what each bit is used for
   //the important thing is linux file descriptors are the best
   int sockfd, portno, n;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char buffer[512];
   
   if (argc < 3) {
      fprintf(stderr,"usage %s hostname port\n", argv[0]);
      exit(0);
   }
	
   portno = atoi(argv[2]);//some way of changing a char array to int
   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	
   server = gethostbyname(argv[1]);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   while(true){
      /* Now read server response */  

      bzero(buffer,sizeof(buffer));
      n = recv(sockfd, buffer, 32,0);
      //use 32 (string size) instead of sizeof(), it stops unexpected behaviour
      //use recv instead of read as its more specialised for socket use
      if (n < 0) {
         perror("ERROR reading from socket");
         exit(1);
      }

      if(*buffer == '\0'){ //check if any data was sent
         break;
      }
      std::cout<<n<<"\t"<<buffer<<std::endl;

      if(*buffer == '\r'){ //check to see if a response is expected
         std::string input;
         std::cin>>input;
         const void* message = input.c_str();
         send(sockfd,message,sizeof(message),0);   
      }
   }

   close(sockfd);
   return 0;
}
