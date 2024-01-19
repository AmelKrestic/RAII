// ConsoleApplication2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <algorithm>
#include <memory>
#include <mutex>
#include "generic_wrapper.h"
#include "basic_shared_ptr.h"
#include "simple_lock.h"
#include "someclass.h"
#include "basic_unique_ptr.h"
std::mutex m;


void mutexTestInternal(int a) {
	simple_lock<std::mutex> l(m);
	if (a==0) {
		std::cout << "Exit through throwing exception" << std::endl;
		throw 0;
	}
	else if (a == 1) {
		std::cout << "Exit through early return" << std::endl;
		return;
	}
	std::cout << "Regular exit" << std::endl;
}

void mutexTest() {
	try {
		mutexTestInternal(0);
	}
	catch (...) {
	}
	mutexTestInternal(1);
	mutexTestInternal(2);
	std::cout << "Mutex is unlocked regardless of exit, else the constructor would have waited on _m.lock()" << std::endl;
}


void genericWrapperTest() {
	{
		someclass s(1, 'g');
		std::cout << "End Of Scope" << std::endl;
	}
	try{
		someclass s(0, 'g');
	}
	catch (...) {
		std::cout << "Exception caught" << std::endl;
	}

}


void basicSharedTest() {
	auto sa = basic_shared_ptr<someclass>::make_shared(1, 'a');
	auto sb = basic_shared_ptr<someclass>::make_shared(1, 'b');
	auto s1 = sa;
	auto s2 = sb;
	auto s3 = s1;

	std::cout << "a count " << sa.count() << std::endl;
	std::cout << "b count " << sb.count() << std::endl;

	{
		auto stemp = sa;
		std::cout << "a count "<<sa.count() << std::endl;
	}
	std::cout << "a count " << sa.count() << std::endl;

	std::swap(s1, s2);
	std::cout << "s1 contents " << (s1->_b) << std::endl;
	std::cout << "s2 contents " << (s2->_b) << std::endl;

	std::cout << "a count " << sa.count() << std::endl;
	std::cout << "b count " << sb.count() << std::endl;

}

void uniqueTest() {
	auto u1 = basic_unique_ptr<someclass>(new someclass(1, 'c'));
	auto u2 = std::move(u1);
	//Moved from pointer used for testing purposes only. Not advised.
	std::cout << "u1 empty?: " << ((u1.operator->()) == nullptr) << std::endl;
	std::cout << "u2 contains: "<< u2->_b << std::endl;
	auto u3 = basic_unique_ptr<someclass>(new someclass(2, 'd'));
	std::swap(u2, u3);
	std::cout << "u2 contains: " << u2->_b << std::endl;
	std::cout << "u3 contains: " << u3->_b << std::endl;
	std::swap(u2, u3);
	std::cout << "u2 contains: " << u2->_b << std::endl;
	std::cout << "u3 contains: " << u3->_b << std::endl;
}

int main()
{
	int* a = new int(5);
	
	mutexTest();
	genericWrapperTest();
	basicSharedTest();
	uniqueTest();
}
