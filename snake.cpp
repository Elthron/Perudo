//install ncurses with sudo apt-get install libncurses5-dev
//compile wiht -lncurses
//slightly shitty snake
#include <ncurses.h>
#include <unistd.h>
#include <utility>      
#include <list>  
#include <stdlib.h>     
#include <time.h>       


class food{
	private:
		std::pair<int,int> location;
		WINDOW* grass;
	public:
		food(WINDOW*);
		void move();
		void draw();
		std::pair<int,int> getLocation();

};

class snake{

	private:
		WINDOW* grass;
		std::pair<int,int> direction; //x,y
		std::pair<int,int> antiDirection; //x,y
		std::list<std::pair<int,int> > snakelist;
		std::list<std::pair<int,int> >::iterator it;
		std::pair<int,int> head; //location at the end of snakelist(needed?)

	public:
		snake(std::pair<int,int>,WINDOW*);
		void move(int,int);
		void draw();
		void setDirection();
		void move();
		void grow();
		int checkCollision();
		int getScore();
		std::pair<int,int> getHead();
};
///////////////////////////////////////////////////////////////////////////////
int main()
{	
	//initialise ncurses
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	curs_set(0);

	start_color();	
	init_color(COLOR_GREEN, 0, 700, 0);
	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	
	int row, col;
	getmaxyx(stdscr, row, col);	
	int splitSize = 4;

	WINDOW *gameWindow = newwin(row - splitSize,col,0,0);
	WINDOW *info = newwin(splitSize,col,row - splitSize,0);
	//setting up the game
	srand (time(NULL));



	std::pair<int,int> startPos;
	startPos.first = col/2;
	startPos.second = row/2;

	snake frodo (startPos,gameWindow);
	food tasty (gameWindow);
	frodo.draw();

	while(frodo.checkCollision()<2){
		wclear(gameWindow);
		frodo.setDirection();
		frodo.move();
		if(frodo.getHead() == tasty.getLocation()){
			tasty.move();
			frodo.grow();
		}
		frodo.draw();
		tasty.draw();
		
		mvwprintw(info,1,1,"score: %d",frodo.getScore());
		
		wborder(gameWindow, '#', '#', '#', '#', '@', '@', '@', '@');
		box(info,0,0);

		wrefresh(gameWindow);	
		wrefresh(info);
		usleep(100000);
	}
	clear();

	attron(A_BOLD);
	mvprintw(row/2 ,col/2 - 4, "Score: %d",frodo.getScore());
	attroff(A_BOLD);
	nodelay(stdscr, false);
	getch();
	endwin();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
snake::snake(std::pair<int,int> coord,WINDOW* gameWindow){
	grass = gameWindow;
	direction.first = 0;//need to define a starting movement
	direction.second = -1;
	antiDirection.first = 0;
	antiDirection.second = 1;
	std::pair<int,int> tail;
	tail.first = coord.first;
	tail.second = coord.second - 1;
	snakelist.push_back(tail);
	snakelist.push_back(coord);
	/*
	clear();
	mvprintw(10,10,"x: %d , y: %d",coord.first,coord.second);
	mvprintw(11,10,"x: %d , y: %d",snakelist[1].first,snakelist[1].second);
	mvprintw(12,10,"x: %d , y: %d",tail.first,tail.second);
	mvprintw(13,10,"x: %d , y: %d",snakelist[0].first,snakelist[0].second);
	mvaddch(snakelist[1].second,snakelist[1].first,ACS_CKBOARD);
	mvaddch(snakelist[0].second,snakelist[0].first,ACS_CKBOARD);
	refresh();
	*/

}

void snake::draw(){
	wattron(grass,COLOR_PAIR(1));
	for(it = snakelist.begin(); it != snakelist.end();++it){
		mvwaddch(grass,it->second,it->first,ACS_CKBOARD);
	}
	wattroff(grass,COLOR_PAIR(1));
	//mvprintw(0,0,"score: %d",getScore());


}

void snake::setDirection(){
	
	int userIn = getch();
	//usleep(100000);
	std::pair<int,int> temp;
	switch(userIn){
		case 'w':
			temp.first=0;
			temp.second=-1;
			if(antiDirection != temp){
				direction.first = 0;
				direction.second = -1;
				antiDirection.first = 0;
				antiDirection.second = 1;
			}
			break;
			
		case 'a':
			temp.first=-1;
			temp.second=0;
			if(antiDirection != temp){
				direction.first = -1;
				direction.second = 0;
				antiDirection.first = 1;
				antiDirection.second = 0;
			}
			break;
		case 's':
			temp.first=0;
			temp.second=1;
			if(antiDirection != temp){
				direction.first = 0;
				direction.second = 1;
				antiDirection.first = 0;
				antiDirection.second = -1;
			}
			break;
		case 'd':
			temp.first=1;
			temp.second=0;
			if(antiDirection != temp){
				direction.first = 1;
				direction.second = 0;
				antiDirection.first = -1;
				antiDirection.second = 0;
			}
			break;
		default:
			break;
	}
}

void snake::move(){
	//get coordinate infront of head
	head.first = snakelist.back().first + direction.first;
	head.second = snakelist.back().second + direction.second;
	snakelist.push_back(head);
	snakelist.erase(snakelist.begin());

}

std::pair<int,int> snake::getHead(){
	return snakelist.back();
}
void snake::grow(){
	std::pair<int,int> temp;
	snakelist.push_front(temp);
}
int snake::checkCollision(){
	int collided = 0;
	for(it = snakelist.begin(); it != snakelist.end();++it){
		if(*it == snakelist.back())
			++collided;	
	}
	if(snakelist.back().first + direction.first == getmaxx(grass)-1 ||snakelist.back().first + direction.first == 0)
		++collided;
	if(snakelist.back().second + direction.second == getmaxy(grass)-1 ||snakelist.back().second + direction.second == 0)
		++collided;
	return collided;
}
int snake::getScore(){
	return snakelist.size();
}
///////////////////////////////////////////////////////////////////////////////
void food::draw(){
	mvwaddch(grass,location.second,location.first,ACS_DIAMOND);
}
void food::move(){
	location.first = rand() % (getmaxx(grass) - 2) + 1;
	location.second = rand() % (getmaxy(grass) - 2) + 1;
	
}
food::food(WINDOW* gameWindow){
	grass = gameWindow;
	move();
	draw();
}

std::pair<int,int> food::getLocation(){
	return location;
}
