#ifndef Q_H_
#define Q_H_

#include "List.h"

class Q : private List
{
	public:
		Q();

		/**
		 * Adds an element to the list in an ordered manner.
		 * @param s the element to push on
		 */
		void push(Sortable *s);
		
		/**
	 	 * Pops an element off the top of the list.
	 	 * @return the element popped off.
	 	 */
		Sortable *pop();
		
		/**
		 * @return true if the list is empty.
		 */
		bool is_empty();
		
		/**
		 * Prints the list
		 */
		void print();
};

#endif /*Q_H_*/
