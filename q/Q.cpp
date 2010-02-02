#include "Q.h"
#include "Sortable.h"

Q::Q() : List() {}

void Q::push(Sortable *s)
{
	if(!m_start) // Empty list
	{
		m_start = new Node(s);
		m_start->setNext(m_start);
		m_start->setPrev(m_start);
	}
	else 
	{
		Node *new_node = new Node(s);
		Node *cur = m_start;
		
		while( cur->getData()->compareTo(s) <= 0 )
		{
			cur = cur->getNext();
			
			if(cur == m_start)
				break; // Looped around
		}
		
		new_node->setNext(cur);
		new_node->setPrev(cur->getPrev());
		cur->getPrev()->setNext(new_node);
		cur->setPrev(new_node);
		
		// We inserted before the first node, so update m_start
		if(cur == m_start && m_start->getData()->compareTo(s) > 0)
			m_start = new_node;
	}	
}

Sortable *Q::pop()
{
	return List::pop();
}

bool Q::is_empty() { return List::is_empty(); }
void Q::print() { List::print(); }
