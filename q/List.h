#ifndef LIST_H_
#define LIST_H_

class Sortable;

/**
 * Implements a double-linked circular list of type Sortable
 */
class List
{
	public:
		List();
		virtual ~List();
	
		/**
		 * Adds a new element to the list
		 * @param s the element to add
		 */
		virtual void push(Sortable *s) = 0;
	
		/**
	 	* Removes the top element from the list.
	 	* @return the element removed.
	 	*/
		Sortable *pop();
		
		/**
		 * @return true if the list is empty.
		 */
		bool is_empty();
		
		/**
		 * Outputs the list
		 */
		void print();
		
	protected:
		class Node { // Nested Node class
			public:
				Node(Sortable *s) : m_data(s), m_next(0), m_prev(0) {}
				~Node();

				Node *getNext() { return m_next; }
				void setNext(Node *n) { m_next = n; }

				Node *getPrev() { return m_prev; }
				void setPrev(Node *n) { m_prev = n; }

				Sortable *getData() { return m_data; }
				void setData(Sortable *s) { m_data = s; }
		
			private:
				Sortable *m_data;
				Node *m_next;
				Node *m_prev;
		};

		Node* m_start;
};

#endif /*LIST_H_*/
