#include "ThreadSafeList.h"

ThreadSafeList():
	head()
{}

~ThreadSafeList()
{}

ThreadSafeList::Node::Node():
	next()
{}

ThreadSafeList::Node::Node(const T& value):
	data(std::make_shared<T>(value)),
	next()
{}

void  ThreadSafeList::push_(const T& item)
{
	std::unique_ptr<Node> new_node(new node(item));
	std::lock_guard<std::mutex> lock(head.m);
	new_node->next=std::move(head.next);
	head.next=std::move(new_node);
}

void erase_if_equal(const T& predicate)
{
	//return on empty list
	if(!head.next())return;
	
	//acquire locks on the head and the first data node
	Node* last_node=&head;
	last_node->m->lock()
	
	Node* current_node=head.next.get();
	
	do
	{
		current_node->m->lock();
		
		//test the predicate against the current node
		if(*(current_node->data) == predicate)	//destroy the node pointed to by current_node
		{
			//give the old node a place die
			std::unique_ptr<Node> old_node(std::move(last_node->next));
			
			//re-assign the pointer of the node before the current one removing the current node form the list
			last_node->next=std::move(current_node->next);
			
			//release the lock on last_node
			last_node->m->unlock();
			
			return;
		}
		
		//step the node pointers forwards
		//unlock the trailing node and set the pointer to point and the current node
		last_node->m->unlock();
		last_node=current_node;
		
		//move the current node along one and acquire a lock
		current_node=current_node->next.get();
	}
	while(current_node)
	
	//release the final held lock (if it gets to this point current_node was NULL so was never locked)
	last_node->m->unlock();
}

void for_each(const U& predicate)
{
	//return on empty list
	if(!head.next())return;
	
	//acquire locks on the head and the first data node
	Node* last_node=&head;
	last_node->m->lock()
	
	Node* current_node=head.next.get();
	
	
	do
	{
		current_node->m->lock();
		
		predicate(current_node->data.get())
		
		//step the node pointers forwards
		//unlock the trailing node and set the pointer to point and the current node
		last_node->m->unlock();
		last_node=current_node;
		
		//move the current node along one and acquire a lock
		current_node=current_node->next.get();
	}
	while(current_node)
	
	//release the final held lock (if it gets to this point current_node was NULL so was never locked)
	last_node->m->unlock();
}
