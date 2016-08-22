#include "wheel.h"

wheel::wheel()
{}

void wheel::push_back(T item)
{
	vec.push_back(item);
}

void wheel::pop_back()
{
	vec.pop_back(item);
}

void wheel::erase(iterator it)
{
	vec.erase( vec.begin()+it.index );
}

unsigned int wheel::size()
{
	return vec.size();
}

wheel::iterator wheel::begin()
{
	return iterator(vec);
}

wheel::iterator wheel::last()
{
	return iterator(vec,vec.size()-1)
}

T wheel::front()
{
	return vec.front();
}

T wheel::back()
{
	return vec.back();
}

wheel::iterator::iterator(std::vector<T>& _vec,unsigned int _index/*=0*/):
	vec(_vec),
	index(_index)
{}

wheel::iterator& wheel::iterator::operator++()
{
	index=(index==vec.size()-1) ? 0 : index+1;
	return *this;
}

wheel::iterator wheel::iterator::operator++(int)
 {
	 iterator retval = *this;
	 ++(*this);
	 return retval;
}

wheel::iterator& wheel::iterator::operator--()
{
	index=(!index) ? vec.size()-1 : index-1;
	return *this;
}

wheel::iterator wheel::iterator::operator--(int)
 {
	 iterator retval = *this;
	 --(*this);
	 return retval;
}

bool operator==(iterator other) const
{
	return index==other.index;
}

bool operator!=(iterator other) const
{
	return !(*this==other);
}

reference operator*() const
{
	return vec[index];
}

T& operator[] (const int index)
{
	int num;
	
	if(abs(index)<vec.size())num=index; //because I don't know how modular arithmetic works
	else num=index%size();
	
	return (num<0) ? vec[vec.size()+num] : vec[num];
}
