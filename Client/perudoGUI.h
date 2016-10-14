#ifndef PERUDO_GUI
#define PERUDO_GUI

#include <ncurses.h>
#include <vector>
#include "client.h"
#include "player.h"

class gui{

	private:
		//game information required to update the screen
		
		
		//window stuff
		int row; //row and col are depend on the size of the terminal window
		int col; 
		int ySplitPosition = 4;//determines how large the box at the bottom is 
		
		
		WINDOW *yourInfo; //yourInfo displays your dice
		WINDOW *gameInfo; //gameInfo displays things to do with other players
		WINDOW *biddingWindow; //biddingWindow is where user input happens 


		void refreshAllWindows(); //calls the wrefresh on all the windows
		void updateGameInfoWindow(); //changes the contents of gameInfo
		void updateYourInfoWindow(); //changes the contents of yourInfo
		void updateBiddingWindow(); //allows the user to submit their bid
		

		void drawDie(int xpos, int pos, int value);
		//this function draws a 7x7 ascii die


	public:
		explicit gui();
		

		~gui(); //ends ncurses mode on destruction
	
		void start();//starts ncurses mode, draws the intial windows
		
		void updateScreen();
		/*this function calls all the other "update" functions and
		refreshes the screen. This may be removed as main might need more
		control over what is updated (e.g. for bidding).
		*/

};

#endif