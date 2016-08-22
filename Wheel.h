#ifndef WHEEL_H
#define WHEEL_H

#include <vector>
#include <algorithm>

//this container class is essentially just a wrapper class for std::vector with iterators designed to wrap around once they reach the last element
//to iterate over the container once please use and indexed for loop with the size() function - the circular nature of the container means that an end() function cannot exist
template <typename T>
class wheel
{
	public:
		explicit wheel();
		
		class iterator : public std::iterator<std::bidirectional_iterator_tag,T,T,const T*,T>
		{
			public:
				explicit iterator(wheel<T>& _wh,unsigned int _index=0);
				
				iterator& operator++();
				iterator operator++(int);
				iterator& operator--();
				iterator operator--(int);
				
				friend iterator operator+(const iterator& lhs, int& rhs);
				friend iterator operator-(const iterator& rhs, int& lhs);
				
				bool operator==(iterator other) const ;
				bool operator!=(iterator other) const;
				
				T& operator*() const;
				
				
			private:
				wheel<T>& wh;
				unsigned int index;
		};
		
		void push_back(T item);
		void pop_back();
		void erase(iterator it);
		unsigned int size();
		iterator begin();
		iterator last();
		T front();
		T back();
		
		T& operator[] (const int index);
		
	private:
		std::vector<T> vec;
};

#endif
