#include "client.h"
#include <stdlib.h>
#include <iostream>
#include <ncurses.h>

void refreshAllWindows(WINDOW*,WINDOW*,WINDOW*);
void updatePlayersWindow(WINDOW *w1,std::vector<playerInfo> players);
void drawDice(WINDOW *w1,int xpos,int ypos,int value);
Bid makeBid(WINDOW *w1);

int main(int argc, char **){

	/*test playerInfo*/
	std::vector<playerInfo> players;

	playerInfo p1,p2,p3;

	p1.numberOfDice = 1;
	p2.numberOfDice = 2;
	p3.numberOfDice = 3;

	p1.name = "frodo";
	p2.name = "johnny";
	p3.name = "BigFish";

	p1.bid.first = 1;
	p1.bid.second = 2;
	p2.bid.first = 3;
	p2.bid.second = 4;
	p3.bid.first = 5;
	p3.bid.second = 6;

	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);	
	/*end of test info*/

	if(argc != 3){
		std::cout<<"Usage: <port> <host>"<<std::endl;
		return 1;
	}

	initscr(); //start ncurses mode
	//noecho();
	cbreak();

	start_color();//lets come up with a pretty colour scheme


	int row, col; //number of rows and collumns of whole screen
	int ySplitPosition = 4; //position from the bottom
	
	getmaxyx(stdscr,row,col);//stdscr is the terminal window

	/*need 3 windows*/
//	int x2 = col/3;
	int y1 = row-ySplitPosition;
	//newwin(height, width, starty, startx);
	//nearly in the right place for all window sizes
	WINDOW *yourInfo = newwin(y1,col/3,0,0);
	WINDOW *gameInfo = newwin(y1,2*col/3,0,1+col/3);
	WINDOW *biddingWindow = newwin(ySplitPosition,col,y1,0);
	
	box(yourInfo,0,0);
	box(gameInfo,0,0);
	box(biddingWindow,0,0);


	refresh(); //for some reason this needs to be here

	updatePlayersWindow(gameInfo,players);
	drawDice(yourInfo,2,2,1);
	drawDice(yourInfo,2+8,2,2);
	drawDice(yourInfo,2+8+8,2,3);
	drawDice(yourInfo,2,2+8,4);
	drawDice(yourInfo,2+8,2+8,5);
	drawDice(yourInfo,2+8+8,2+8,6);


	refreshAllWindows(yourInfo,gameInfo,biddingWindow);
	Bid bid = makeBid(biddingWindow);
	mvwprintw(biddingWindow,2,1,"%d %d",bid.first,bid.second);
	wrefresh(biddingWindow);
/*
	client frodo;
	int portno = atoi(argv[1]);
	frodo.connectToServer(portno,&argv[2]);
	frodo.getServerData();
	frodo.getServerData();
	frodo.getServerData();
	frodo.getServerData();
*/
	
	getch();//wait for keystroke
	endwin();//end ncurses mode

	return 0;
}

void refreshAllWindows(WINDOW *w1,WINDOW *w2, WINDOW *w3){
	wrefresh(w1);
	wrefresh(w2);
	wrefresh(w3);
}

void updatePlayersWindow(WINDOW *w1,std::vector<playerInfo> players){
	//make 3 lists of info
	int x = getmaxx(w1);
	int y = 2;
	//titles
	wattron(w1,A_BOLD | A_UNDERLINE);
	mvwprintw(w1,1,1,"Name");
	mvwprintw(w1,1,1+x/3,"Number of Dice");
	mvwprintw(w1,1,1+2*x/3,"Bid");	
	wattroff(w1,A_BOLD | A_UNDERLINE);

	std::vector<playerInfo>::iterator it;
	for(it = players.begin();it != players.end();++it,++y){
		mvwprintw(w1,y,1,"%s",it->name.c_str());
		mvwprintw(w1,y,1+x/3,"%d",it->numberOfDice);
		mvwprintw(w1,y,1+2*x/3,"%d %d", it->bid.first,it->bid.second);
	}

}

void drawDice(WINDOW *w1, int xpos, int ypos, int value){
	//dont worry, its not as scary as it looks...
	switch(value){

		case 1:
			//first row
			mvwaddch(w1,ypos,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			//second row...
			mvwaddch(w1,ypos+1,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+2,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+3,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+4,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+5,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+6,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			break;
		case 2:
			mvwaddch(w1,ypos,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+1,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+2,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+3,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+4,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+5,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+6,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			break;
		case 3:
			mvwaddch(w1,ypos,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+1,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+2,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+3,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+4,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+5,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+6,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			break;
		case 4:
			mvwaddch(w1,ypos,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+1,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+2,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+3,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+4,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+5,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+6,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			break;
		case 5:
			mvwaddch(w1,ypos,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+1,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+2,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+3,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+4,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+5,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+6,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			break;
		case 6:
			mvwaddch(w1,ypos,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+1,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+2,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+3,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+4,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+5,xpos,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,' ');waddch(w1,ACS_CKBOARD);
			mvwaddch(w1,ypos+6,xpos,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);waddch(w1,ACS_CKBOARD);
			break;
		default:
			break;
		
	}

}

Bid makeBid(WINDOW *w1){
	
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN,COLOR_BLACK);
	
	wattron(w1,COLOR_PAIR(1));
	mvwaddch(w1,1,1,ACS_CKBOARD);
	wattroff(w1,COLOR_PAIR(1));
	Bid bid;
	wprintw(w1,"\tPlease enter your bid <Number of Dice> <Value of Dice>:");
	wrefresh(w1);
	wscanw(w1,"%d %d",&bid.first,&bid.second);
	//user control!
	//mvwprintw(w1,2,1,"%d %d",bid.first,bid.second);
	wrefresh(w1);
	return bid;
}