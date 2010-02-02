#ifndef SORTABLE_H_
#define SORTABLE_H_

//#include <string>

using namespace std;

/**
 * class Sortable
 * Essentially an interface for sortable elements,
 * with virtual methods to compare 2 elements, and
 * to represent as a string. */
class Sortable
{
	public:
		Sortable() {};
		/**
		 * Compares this to another for order.
		 * @param s the class to compare to
		 * @return (s - this)
		 */
		virtual int compareTo (Sortable *s1) = 0; // Pure virtual
		//virtual string toString() = 0;
};

#endif /*SORTABLE_H_*/
