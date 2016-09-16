#ifndef THREAD_SAFE_LIST_H
#define THREAD_SAFE_LIST_H

#include <memory>
#include <mutex>

//class that implements a list that can be accessed safely by an arbitrary number of threads
//
//the class features four functions: push_front(const T& item), pop_front(), erase_if_equal(T& predicate) and for_each<U>(U& predicate)
//the first two do what you think they do
//erase_if_equal(T& predicate) removes the FIRST encountered instance of "predicate" from the list
//for_each<U>(U& predicate) enacts predicate on every element of the list
//
//note that there is an unfortunate but neccessary vulnerability in the for_each() function
//	-it is possible for the functor to return handles to the stored objects so that the calling thread can modify them at an arbitrary later time
//this vulnerability is necessary to allow more concurrent access to the list but please do not write functors that do this

template<typename T>
class ThreadSafeList
{
	private:
		
		//class for the nodes of the list
		//---------------------------------------------------------------------------------
		struct Node
		{
			Node() : next() {}
			Node(const T& value) : data(std::make_shared<T>(value)) , next() {}
			
			//the mutex to lock when the node is being modified
			std::mutex m;
			//the stored data item
			std::shared_ptr <T> data;
			//the pointer to the next node
			std::unique_ptr<Node> next;
		};
		//---------------------------------------------------------------------------------
	
	//dummy head node
	Node head;
	
	public:
		//ctor/dtor
		explicit ThreadSafeList() {}
		~ThreadSafeList() {}
		
		//deny copying and assignment
		ThreadSafeList(const ThreadSafeList& other)=delete;
		ThreadSafeList& operator=(const ThreadSafeList& other)=delete;
		
		void  push_front(const T& item)
		{
			//create the new node
			std::unique_ptr<Node> new_node(new Node(item));
			//lock-guard the head mutex
			std::lock_guard<std::mutex> lock(head.m);
			//set the new node's next pointer to the current head
			new_node->next=std::move(head.next);
			//set the head to the new node
			head.next=std::move(new_node);
		}
		
		T pop_front()
		{
			//lock the head and the first data node
			std::lock_guard<std::mutex> lock1(head.m);
			std::lock_guard<std::mutex> lock2(head.next->m);
			
			//move the data node to a dummy node
			std::unique_ptr<Node> old_node=std::move(head.next);
			
			//move the second data node to the poistion of the old first node
			head.next=std::move(old_node->next);
			
			//return the data of the old node
			return *(old_node->data);
		}
		
		void erase_if_equal(const T& predicate)
		{
			//acquire a lock on the head
			Node* last_node=&head;
			last_node->m.lock();
			
			//get a pointer to the node after the head
			Node* current_node=head.next.get();
			
			while(current_node)
			{
				current_node->m.lock();
				
				//test the predicate against the current node
				if(*(current_node->data) == predicate)
				{
					//destroy the node pointed to by current_node...
					
					//give the old node a place die
					std::unique_ptr<Node> old_node(std::move(last_node->next));
					
					//re-assign the pointer of the node before the current one removing the current node form the list
					last_node->next=std::move(current_node->next);
					
					//release the lock on last_node (no need to unlock current_node as it is soon to be destroyed)
					last_node->m.unlock();
					
					return;
				}
				
				//step the node pointers forwards...
				
				//unlock the trailing node and set the pointer to point and the current node
				last_node->m.unlock();
				last_node=current_node;
				
				//move the current node along one and acquire a lock
				current_node=current_node->next.get();
			}
			
			//if the end of the list was reached without returning, release the final held lock
			//(if it gets to this point current_node was nullptr so was never locked)
			last_node->m.unlock();
		}
		
		//enact "predicate" on the node::data of each element in the list
		//predicate should be a function with an overload of () that takes a single argument of type T
		template<typename U>
		void for_each(U& predicate)
		{
			//acquire a lock on the head
			Node* last_node=&head;
			last_node->m.lock();
			
			//get a pointer to the node after the head
			Node* current_node=head.next.get();
			
			
			while(current_node)
			{
				current_node->m.lock();
				
				//enact the predicate
				predicate( *( current_node->data.get() ) );
				
				//step the node pointers forwards
				//unlock the trailing node and set the pointer to point and the current node
				last_node->m.unlock();
				last_node=current_node;
				
				//move the current node along one and acquire a lock
				current_node=current_node->next.get();
			}
			
			//release the final held lock (at this point current_node is nullptr so was never locked)
			last_node->m.unlock();
		}
		
};

#endif
