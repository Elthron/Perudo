#include "Human.h"

clientManager* Human::mgr;

Human::Human(int _client_id):
	Player(6),
	client_id(_client_id)
{}

Bid* Human::takeTurn(Bid* last_bid)
{
	if(last_bid)return nullptr;
	else return new Bid(1,1);
}

void Human::sendBid(Bid* /*bid*/)
{
	//idgaf
}

void Human::setMgr(clientManager* _mgr)
{
	mgr=_mgr;
}