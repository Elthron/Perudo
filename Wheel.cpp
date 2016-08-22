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
	return iterator(*this);
}

wheel::iterator wheel::last()
{
	return iterator(*this,vec.size()-1);
}

T wheel::front()
{
	return vec.front();
}

T wheel::back()
{
	return vec.back();
}

wheel::iterator::iterator(std::vector<T>& _wh,unsigned int _index/*=0*/):
	wh(_wh),
	index(_index)
{}

wheel::iterator& wheel::iterator::operator++()
{
	index=(index==wh.size()-1) ? 0 : index+1;
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
	index=(!index) ? wh.size()-1 : index-1;
	return *this;
}

wheel::iterator wheel::iterator::operator--(int)
 {
	 iterator retval = *this;
	 --(*this);
	 return retval;
}

bool wheel::iterator::operator==(iterator other) const
{
	return index==other.index;
}

bool wheel::iterator::operator!=(iterator other) const
{
	return !(*this==other);
}

T& wheel::iterator::operator*() const
{
	return wh[index];
}

wheel::iterator operator+(const iterator& lhs, int& rhs)
{
	lhs.index+=rhs;
}

wheel::iterator operator-(const iterator& rhs, int& lhs)
{
	lhs.index-=rhs;
}

T& operator[] (const int index)
{
	int num;
	
	if(abs(index)<vec.size())num=index; //because I don't know how modular arithmetic works
	else num=index%size();
	
	return (num<0) ? vec[vec.size()+num] : vec[num];
}
