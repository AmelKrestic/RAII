#pragma once
#include <iostream>
class someclass {
	int _a;
	int _b;
public:
	someclass(int a, char b) {
		_a = a;
		_b = b;
		std::cout << a << " " << b << std::endl;
	}
};