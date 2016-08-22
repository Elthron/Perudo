#include "Die.h"

std::mt19937 Die::twister();

Die::Die(unsigned int _sides/*=6*/):
	sides(sides),
	current_value(1),
	distribution(1,sides)
{}

unsigned int roll()
{
	current_value=distribution(twister);
	return current_value;
}

unsigned int getValue() const
{
	return current_value;
}

void Die::seed(unsigned int _seed)
{
	twister.seed(_seed);
}
