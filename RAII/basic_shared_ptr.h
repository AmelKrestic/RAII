#pragma once
#include <algorithm>
#include <iostream>
#include <memory>

template<class T>
class basic_shared_ptr {
private:
	T* _data; //Object held by the pointer
	int* _count; //Count of references to object
	//dynamically allocated, as otherwise it could not be shared across pointers
	/*
	* Basic constructor with varidic argument list.
	*/
	template<class... Args>
	basic_shared_ptr(Args... args) {
		_data = new T(args...);
		_count = new int(1);
	}
	/*
	* Creates an entirely empty pointer.
	*/
	basic_shared_ptr() {
	}
public:
	/*
	* Copy constructor.
	* Acquires the pointers from the other shared pointer 
	* and adds to the total current count.
	*/
	basic_shared_ptr(const basic_shared_ptr& g) {
		_data = g._data;
		_count = g._count;
		(*_count)++;
	}

	/*
	* Move constructor.
	* Takes contents of other pointer, overwriting them with nullptrs
	* count not incremented since same number of pointers point to object
	*/
	basic_shared_ptr(basic_shared_ptr&& g) noexcept{
		_data = g._data;
		g._data = nullptr;
		_count = g._count;
		g._count = nullptr;
		
	}
	/*
	* Copy assignment.
	* Simply calls copy constructor with given pointer.
	*/
	basic_shared_ptr& operator=(const basic_shared_ptr& g) {
		return *this=basic_shared_ptr(g);
	}
	/*
	* Move assignment.
	* Swaps contents of given pointer and self.
	*/
	basic_shared_ptr& operator=(basic_shared_ptr&& g) noexcept{
		std::swap(_data, g._data);
		std::swap(_count, g._count);
		return *this;
	}
	/*
	* Static method for creating shared pointer with given parameters for the held object.
	* Since no regular public constructor exists, this is the only way to create a pointer
	* thus removing the need to use new.
	*/
	template<class... Args>
	static basic_shared_ptr<T> make_shared(Args... args) {
		basic_shared_ptr<T> t(args...);
		return t;
	}

	/*
	* Destructor.
	* Decrements the count of a non empty pointer and deletes it once it reaches zero,
	* i.e. when no other pointers to the object exist anymore.
	* Guarantees that object is destroyed at some point and that delete is not called multiple times.
	* This is only the case in non concurrent programs.
	*/
	~basic_shared_ptr() {
		if (_data != nullptr) {
			(*_count)--;
			std::cout << "Shared count now:" << *_count << std::endl;
			if (*_count == 0) {
				delete _data;
				delete _count;
				std::cout << "Shared object deleted" << std::endl;
			}
		}
	}
	/*
	* Expose _data pointer/underlying object
	*/
	T& operator*() const {
		return *_data;
	}
	T* operator->() const {
		return _data;
	}
	/*
	* Returns current count (0 for empty pointer)
	*/
	int count() const {
		if (_count == nullptr) {
			return 0;
		}
		return *_count;
	}
};