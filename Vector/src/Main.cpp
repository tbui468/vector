/*
IMPLEMENT FULL VECTOR CLASS FROM STD
************************************
IMPLEMENT SUNDAY**********************
-default initialize<T>()
-push_back() (need to implement private iterator to keep track of end of array)
-private: array_size (different from size(), which is the number of elements)
-size() (returns the number elements in array, NOT the size of the array)
-private:resize() (needs to copy array into new larger array, and delete old array, fix pointer)
-reserve() (resize to set size (without fill data))

BUG!!! Can't create vector::Vector<vector::Vector<int>>.  FIXED!!!! 
If I rewrite destructor, copy constructor or copy assignment operator, rewrite all three!!!
()
IMPLEMENT MONDAY*****************
-how to include iterator types in the format vector::Vector<int>::iterator iter = vec.begin();
-remove-erase idiom functions
-emplace_back takes in parameters to create object and insert (as opposed to copying object in push_back)
-read reference to make sure return types of functions are the same
-study the other functions necessary

IMPLEMENT TUESDAY****************
-Implement the remaining functions

IMPLEMENT WEDNESDAY****************
-write comprehensive unit tests for each function (public and private) for regular use and edge cases (eg, size 0)

IMPLEMENT THURSDAY******************
-write a base class (Iterable, Container, etc) that Vector inherits from

IMPLEMENT FRIDAY**********************
-Write a map class that inherits from the same base classes as Vector

SATURDAY*******************************
-Code review
-compare it to the source code of the Standard Library


*/




#include <iostream>
#include <vector>
#include <algorithm>
#include "Vector.h"




int main() {

	std::cout << "Hello World" << std::endl;

	std::vector<int> v1;

	for (int i = 0; i < 10; ++i) {
		v1.push_back(i);
	}

	v1.erase(v1.begin());

	for (int i : v1) {
		std::cout << i << ", " << std::flush;
	}
	
	std::cin.get();



	return 0;
}