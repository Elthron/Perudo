#ifndef BID_H
#define BID_H

//header to define the bid proxy object and various relevant overloads

//in this game a "bid" is a std::pair of ints: 4 2s -> std::pair<unsigned int,unsigned int> {4,2}
typedef std::pair<unsigned int,unsigned int> Bid;

//function to return the "value" of a bid - ones are worth "2", other numbers are worth "1"
unsigned int getBidValue(const Bid& bid);

//logical operators
bool operator<(const Bid& lhs, const Bid& rhs);
bool operator>(const Bid& lhs, const Bid& rhs);
bool operator==(const Bid& lhs, const Bid& rhs);
bool operator!=(const Bid& lhs, const Bid& rhs);
bool operator<=(const Bid& lhs, const Bid& rhs);
bool operator>=(const Bid& lhs, const Bid& rhs);

#endif
