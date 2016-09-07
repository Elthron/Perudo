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
			Node() : next() {}
			Node(const T& value) : data(std::make_shared<T>(value)) , next() {}
			
			std::mutex m;
			std::shared_ptr <T> data;
			std::unique_ptr<Node> next;
		};
	
	//dummy head node
	Node head;
	
	public:
		//ctor/dtor
		explicit ThreadSafeList() {}
		~ThreadSafeList() {}
		
		//deny copying and assignment
		ThreadSafeList(const ThreadSafeList& other)=delete;
		ThreadSafeList& operator=(const ThreadSafeList& other)=delete;
		
		//this function does what you think
		void  push_front(const T& item)
		{
			std::unique_ptr<Node> new_node(new Node(item));
			std::lock_guard<std::mutex> lock(head.m);
			new_node->next=std::move(head.next);
			head.next=std::move(new_node);
		}
		
		//remove the 1st node with data==predicate
		void erase_if_equal(const T& predicate)
		{
			//return on empty list
			if(!head.next())return;
			
			//acquire locks on the head and the first data node
			Node* last_node=&head;
			last_node->m.lock();
			
			Node* current_node=head.next.get();
			
			do
			{
				current_node->m.lock();
				
				//test the predicate against the current node
				if(*(current_node->data) == predicate)	//destroy the node pointed to by current_node
				{
					//give the old node a place die
					std::unique_ptr<Node> old_node(std::move(last_node->next));
					
					//re-assign the pointer of the node before the current one removing the current node form the list
					last_node->next=std::move(current_node->next);
					
					//release the lock on last_node
					last_node.m.unlock();
					
					return;
				}
				
				//step the node pointers forwards
				//unlock the trailing node and set the pointer to point and the current node
				last_node->m.unlock();
				last_node=current_node;
				
				//move the current node along one and acquire a lock
				current_node=current_node->next.get();
			}
			while(current_node);
			
			//release the final held lock (if it gets to this point current_node was NULL so was never locked)
			last_node->m.unlock();
		}
		
		//enact "predicate" on the node::data of each element in the list
		//predicate should be a function with an overload of () that takes a single argument of type T
		template<typename U>
		void for_each(U& predicate)
		{
			//return on empty list
			if(!head.next.get())return;
			
			//acquire locks on the head and the first data node
			Node* last_node=&head;
			last_node->m.lock();
	
			Node* current_node=head.next.get();
			
			
			do
			{
				current_node->m.lock();
				
				predicate( *( current_node->data.get() ) );
				
				//step the node pointers forwards
				//unlock the trailing node and set the pointer to point and the current node
				last_node->m.unlock();
				last_node=current_node;
				
				//move the current node along one and acquire a lock
				current_node=current_node->next.get();
			}
			while(current_node);
			
			//release the final held lock (if it gets to this point current_node was NULL so was never locked)
			last_node->m.unlock();
		}
		
};

#endif
