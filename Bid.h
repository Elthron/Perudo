#ifndef BID_H
#define BID_H

#include <utility>

//header to define the bid proxy object and various relevant overloads

//in this game a "bid" is a std::pair of ints: 4 2s -> std::pair<unsigned int,unsigned int> {4,2}
typedef std::pair<unsigned int,unsigned int> Bid;

//function to return the "value" of a bid
//an arcane formula of great power is used to uniquely map the bid onto the following grid
//      |  1  | 2 | 3 | 4 | 5 | 6
//--------------------------------
//  1 |   10    0   1   2   3   4
//  2 |   21    5   6   7   8   9
//  3 |   32   11  12  13  14  15
//  4 |   43   16  17  18  19  20
//  5 |   54   22  23  24  25  26
//  6 |   65   27  28  29  30  31
//  7 |   76   33  34  35  36  37
//  ..|   ..   ..  ..  ..  ..  ..
unsigned int getBidValue(const Bid& bid);

//logical operators
bool operator<(const Bid& lhs, const Bid& rhs);
bool operator>(const Bid& lhs, const Bid& rhs);
bool operator==(const Bid& lhs, const Bid& rhs);
bool operator!=(const Bid& lhs, const Bid& rhs);
bool operator<=(const Bid& lhs, const Bid& rhs);
bool operator>=(const Bid& lhs, const Bid& rhs);
bool operator !(const Bid& bid);

#endif
