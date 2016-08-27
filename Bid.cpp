#include "Bid.h"

unsigned int getValue(const Bid& bid)
{
	return bid->first* ((bid->second==1) ? 2 : 1);
}

//note that operator< is the only one that need actually be defined as all the other operators can be written in terms of it
bool operator<(const Bid& lhs, const Bid& rhs)
{
	return getBidValue(lhs)<getBidValue(rhs);
}

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
