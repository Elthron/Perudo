#include "perudoGUI.h"
//todo: give it a pointer to a list of pointers which point to player
gui::gui(){

}

gui::~gui(){
	endwin();
}

void gui::start(){
	initscr(); //start ncurses mode
	cbreak();
	//curs_set(0);
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN,COLOR_BLACK);
	
	getmaxyx(stdscr,row,col);

	int x2 = col/3;
	int y1 = row-ySplitPosition;

	//nearly in the right place for all window sizes
	yourInfo = newwin(y1,col/3,0,0);
	gameInfo = newwin(y1,2*col/3,0,1+col/3);
	biddingWindow = newwin(ySplitPosition,col,y1,0);
	
	box(yourInfo,0,0);
	box(gameInfo,0,0);
	box(biddingWindow,0,0);
	
	refresh(); //i think this is needed
	this->refreshAllWindows();
}


void gui::refreshAllWindows(){
	
	wrefresh(yourInfo);
	wrefresh(gameInfo);
	wrefresh(biddingWindow);
}

void gui::updateScreen(){
	this->updateGameInfoWindow();
	this->updateYourInfoWindow();
	this->refreshAllWindows();
	this->updateBiddingWindow();
	this->updateGameInfoWindow();
	this->refreshAllWindows();
}

void gui::updateGameInfoWindow(){
	//make 3 'lists' of info
	int x = getmaxx(gameInfo);
	int y = 2;
	//titles
	wattron(gameInfo,A_BOLD | A_UNDERLINE);
	mvwprintw(gameInfo,1,1,"Name");
	mvwprintw(gameInfo,1,1+x/3,"Number of Dice");
	mvwprintw(gameInfo,1,1+2*x/3,"Bid");	
	wattroff(gameInfo,A_BOLD | A_UNDERLINE);
/*
	std::vector<playerInfo*>::iterator it;
	for(it = players.begin();it != players.end();++it,++y){
		mvwprintw(gameInfo,y,1,"%s",(*it)->name.c_str());
		mvwprintw(gameInfo,y,1+x/3,"%d",(*it)->numberOfDice);
		mvwprintw(gameInfo,y,1+2*x/3,"%d %d",(*it)->bid.first,(*it)->bid.second);
	}
*/
}

void gui::updateYourInfoWindow(){
	for (int i = 0,k = 0; i < 2; ++i){//col
		for (int j = 0; j < 3; ++j){//row
			drawDie(2+8*j,2+8*i,dice[k]);
			++k;
		}
		
	}

}

void gui::updateBiddingWindow(){
	/*
	int x;
	int y;
	wclear(biddingWindow);
	box(biddingWindow,0,0);
	wattron(biddingWindow,COLOR_PAIR(1));
	mvwaddch(biddingWindow,1,1,ACS_CKBOARD);
	wattroff(biddingWindow,COLOR_PAIR(1));
	wprintw(biddingWindow,"\tPlease enter your bid <Number of Dice> <Value of Dice>:");
	wrefresh(biddingWindow);
	wscanw(biddingWindow,"%d %d",&me.bid.first,&me.bid.second);
	//user control!
	mvwprintw(biddingWindow,2,1,"%d %d",me.bid.first,me.bid.second);
	*/
}

void gui::drawDie(int xpos, int ypos, int value){
	//dont worry, its not as scary as it looks... (there may have been a better way but ctrl+c ctrl+v exists)
	switch(value){

		case 1:
			//first row
			mvwaddch(yourInfo,ypos,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			//second row...
			mvwaddch(yourInfo,ypos+1,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+2,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+3,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+4,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+5,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+6,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			break;
		case 2:
			mvwaddch(yourInfo,ypos,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+1,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+2,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+3,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+4,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+5,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+6,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			break;
		case 3:
			mvwaddch(yourInfo,ypos,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+1,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+2,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+3,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+4,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+5,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+6,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			break;
		case 4:
			mvwaddch(yourInfo,ypos,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+1,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+2,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+3,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+4,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+5,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+6,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			break;
		case 5:
			mvwaddch(yourInfo,ypos,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+1,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+2,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+3,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+4,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+5,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+6,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			break;
		case 6:
			mvwaddch(yourInfo,ypos,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+1,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+2,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+3,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+4,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+5,xpos,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,' ');waddch(yourInfo,ACS_CKBOARD);
			mvwaddch(yourInfo,ypos+6,xpos,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);waddch(yourInfo,ACS_CKBOARD);
			break;
		default:
			break;
		
	}

}