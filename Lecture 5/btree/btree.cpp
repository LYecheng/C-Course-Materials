#include "btree.h"

btree f() {
	btree result;
	result.insert(0);
	result.insert(5);
	result.insert(2);
	return result;
}
int main()
{
	// New object constructed from temporary. Uses move constructor because OK to cannibalize temporary.
	btree t1(f());
	btree t2{ f() }; // Same comment for uniform initializer
	btree t3 = f();  // Same comment for copy initializer

	// New objects constructed from existing named object. Uses copy constructor because existing object needs
	// to be protected for future use
	btree t4(t1);
	btree t5{ t1 };  // Same comment for uniform initializer
	btree t6  = t1;  // Same comment for copy initializer

	// Not creating a new object, but using assignment to modify an existing object, so
	// assignment operators (i.e., operator=) are used rather than constructors
	t2 = f(); // Move assignment because the return value of f() is temporary and can be cannibalized
	t2 = t1; // Copy assignment because the user never said t1 could be changed
	t2 = std::move(t1);  // Move assignment because the user specifically said they don't
	                     // care about t1 any more and we are free to cannibalize it
	return 0;
}