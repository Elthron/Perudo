#include <cmath>
#include "Bid.h"

unsigned int getBidValue(const Bid& bid)
{
	//perform differently for a one
	if(bid.second==1)return bid.first*10+bid.first-1;
	//just trust the formula - I've tested it
	else return 5.5*bid.first+bid.second-7.75-0.25*std::pow(-1,bid.first);
}

//note that operator< is the only one that need actually be defined as all the other operators can be written in terms of it
bool operator<(const Bid& lhs, const Bid& rhs)
{
	//compare the values of the two bids
	return getBidValue(lhs)<getBidValue(rhs);
}

//standard definitions of the logical operators
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool operator>(const Bid& lhs, const Bid& rhs)
{
	return !(lhs<rhs) && (lhs!=rhs);
}

bool operator==(const Bid& lhs, const Bid& rhs)
{
	return !(lhs<rhs) && !(lhs<rhs);
}

bool operator!=(const Bid& lhs, const Bid& rhs)
{
	return !(rhs==lhs);
}

bool operator<=(const Bid& lhs, const Bid& rhs)
{
	return !(lhs>rhs);
}

bool operator>=(const Bid& lhs, const Bid& rhs)
{
	return !(lhs<rhs);
}
