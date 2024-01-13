#pragma once
#include "generic_wrapper.h"
/*
* Basic Class for Testing purposes
*/
class someclass {
public:
	//public for ease of access.
	char _b;
	generic_wrapper<int> _safe_container;

	/*
	* Simple constructor.
	* Sets values of all members.
	* Throws an exception if a is 0. Destructor (if existant) wouldn't be called,
	* but all fully constructed member destructors are called, and thus
	* no resources are leaked.
	*/
	someclass(int a, char b) {
		_safe_container= generic_wrapper<int>(a);
		if (a == 0) {
			throw 0;
		}
		_b=char(b);
	}
	//No need for a destructor
	//Destructors of members are called when object of this class exists scope
};