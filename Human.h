#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class clientManager;

class Human : public Player
{
	public:
		explicit Human(int _client_id);
		
		//function to ask the human to take their turn 
		virtual Bid* takeTurn();
		//function to send a generaic message to the client side
		virtual void notify(Message& message);
		
		void roll();
		
		static void setMgr(clientManager* _mgr);
		
	private:
		int client_id;
		
		static clientManager* mgr;
};

#endif