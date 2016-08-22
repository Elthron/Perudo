#ifndef THREAD_SAFE_LIST_H
#define THREAD_SAFE_LIST_H

#include <memory>
#include <mutex>

template<typename T>
class ThreadSafeList
{
	private:
		
		//class for the nodes of the list
		struct Node
		{
			Node();
			Node(const T& value);
			
			std::mutex m;
			std::unique_ptr <T> data;
			std::unique_ptr<Node> next;
		};
	
	//dummy head node
	Node head;
	
	public:
		//ctor/dtor
		explicit ThreadSafeList();
		~ThreadSafeList();
		
		//deny copying and assignment
		ThreadSafeList(const ThreadSafeList& other)=delete;
		ThreadSafeList& operator=(const ThreadSafeList& other)=delete;
		
		//this function does what you think
		void  push_front(const T& item);
		
		//remove the 1st node with data==predicate
		void erase_if_equal(const T& predicate);
		
		//enact "predicate" on the node::data of each element in the list
		//predicate should be a function with an overload of () that takes a single argument of type T
		template<typename U>
		void for_each(const U& predicate);
		
		
}

#endif
