//#include <iostream>
#include "List.h"
#include "Sortable.h"

using namespace std;

List::List() : m_start(0) {}

List::~List()
{
	Node *cur = m_start;
	m_start->getPrev()->setNext(0); // Cut circular pointer
	Node *next = 0;
	do {
		next = cur->getNext();
		delete cur;
		cur = next;
	} while(cur!=0);
}

Sortable *List::pop()
{
	if(!m_start)
		return 0;
		
	Sortable *ret = m_start->getData();
	if(m_start->getNext()==m_start)
		m_start = 0; // Single item list
	else {
		m_start->getPrev()->setNext(m_start->getNext());
		m_start->getNext()->setPrev(m_start->getPrev());
		m_start = m_start->getNext();
	}
	
	return ret;
}

bool List::is_empty() { return !m_start; }

void List::print()
{
	if(!m_start) return; // empty list
	Node *cur = m_start;
	
	while(true)
	{
		//cout << cur->getData()->toString() << endl;
		cur = cur->getNext();
		if(cur==m_start) // looped all the way around
			break;
	}
}

List::Node::~Node() /// Needs to be declared after Sortable is included
{
	//cout << "Deleting node " << this << endl;
}
