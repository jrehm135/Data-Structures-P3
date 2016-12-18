#include <string>
#include <cxxtest/TestSuite.h>

#include "linked_list.h"

#include <cstdlib>
#include <stack>

template class LinkedList<int>;

class LinkedListTests : public CxxTest::TestSuite
{
public:
   void testTODO( void )
   {
	   LinkedList<int> c;
	   TS_ASSERT(c.isEmpty() == true);
	   c.insert(0, 1);
	   TS_ASSERT(c.isEmpty() == false);
	   TS_ASSERT(c.getLength() == 1);
	   TS_ASSERT(c.getEntry(0) == 1);
	   c.setEntry(0, 2);
	   TS_ASSERT(c.getLength() == 1);
	   TS_ASSERT(c.getEntry(0) == 2);
	   c.insert(1,3);
	   TS_ASSERT(c.getLength() == 2);
	   TS_ASSERT(c.getEntry(0) == 2);
	   TS_ASSERT(c.getEntry(1) == 3);
	   c.remove(1);
	   TS_ASSERT(c.getLength() == 1);
	   TS_ASSERT(c.isEmpty() == false);
	   c.insert(1, 4);
	   c.insert(1, 5);
	   TS_ASSERT(c.getEntry(1) == 5);
	   TS_ASSERT(c.getEntry(2) == 4);
	   c.remove(1);
	   TS_ASSERT(c.getEntry(1) == 4);
	   TS_ASSERT_THROWS(c.getEntry(2), std::range_error);
	   TS_ASSERT_THROWS(c.setEntry(2, 6), std::range_error);
	   TS_ASSERT(c.getEntry(1) == 4);
	   TS_ASSERT_THROWS(c.insert(3,7), std::range_error);
	   TS_ASSERT_THROWS(c.remove(2), std::range_error);
	   LinkedList<int> d(c);
	   TS_ASSERT(d.getEntry(1) == 4);
	   LinkedList<int> e;
	   LinkedList<int> f;
	   e.insert(0, 8);
	   f = e;
	   TS_ASSERT(e.getEntry(0) == 8);
	   TS_ASSERT(f.getEntry(0) == 8);
	   e.insert(1, 9);
	   e.clear();
	   TS_ASSERT_THROWS(e.getEntry(0), std::range_error);
   }  
};
