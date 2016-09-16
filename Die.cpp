#include "Die.h"

//initialisation of static member
std::mt19937 Die::twister;

//the rest is pretty self explanitory

Die::Die(unsigned int _sides/*=6*/):
	sides(_sides),
	current_value(1),
	distribution(1,sides)
{}

unsigned int Die::roll()
{
	current_value=distribution(twister);
	return getValue();
}

unsigned int Die::getValue() const
{
	return current_value;
}

void Die::seed(unsigned int _seed)
{
	twister.seed(_seed);
}
