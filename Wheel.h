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
		explicit wheel() {}
		
		class iterator : public std::iterator<std::bidirectional_iterator_tag,T,T,const T*,T>
		{
			public:
				friend class wheel;
				
				explicit iterator(wheel<T>& _wh,unsigned int _index=0) : wh(_wh),index(_index) {}
				
				iterator& operator++()
				{
					index=(index==wh.size()-1) ? 0 : index+1;
					return *this;
				}
				
				iterator operator++(int)
				{
					iterator retval = *this;
					++(*this);
					return retval;
				}
				
				iterator& operator--()
				{
					index=(!index) ? wh.size()-1 : index-1;
					return *this;
				}
				
				iterator operator--(int)
				{
					iterator retval = *this;
					--(*this);
					return retval;
				}
				
				iterator operator+(const int& rhs)
				{
					return iterator(wh,index+=rhs);
				}
				
				iterator operator-(const int& rhs)
				{
					return iterator(wh,index-=rhs);
				}
				
				bool operator==(iterator other) const {return index==other.index;}
				bool operator!=(iterator other) const {return !(*this==other);}
				
				T& operator*() const {return wh[index];}
				
				
			private:
				wheel<T>& wh;
				unsigned int index;
		};
		
		void push_back(T item) {vec.push_back(item);}
		
		void pop_back() {vec.pop_back();}
		
		void erase(iterator it) {vec.erase( vec.begin()+it.index );}
		
		unsigned int size() {return vec.size();}
		
		iterator begin() {return iterator(*this);}
		
		iterator last() {return iterator(*this,vec.size()-1);}
		
		T front() {return vec.front();}
		
		T back() {return vec.back();}
		
		T& operator[] (const int index)
		{
			int num;
			
			if( abs(index) < static_cast<int>( vec.size() ) )num=index; //because I don't know how modular arithmetic works
			else num=index%size();
	
			return (num<0) ? vec[vec.size()+num] : vec[num];
		}
		
	private:
		std::vector<T> vec;
};

#endif
