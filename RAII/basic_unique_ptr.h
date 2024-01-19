#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
template<typename T>
class basic_unique_ptr {
private:
	//object owned by this pointer
	T* _data;
public:
	/*
	* Basic constructor and destructor
	*/
	basic_unique_ptr(T* t = nullptr) :_data(t) {}
	~basic_unique_ptr() {
		delete _data;
		std::cout << "pointer destructor called" << std::endl;
	}
	//Copy Constructor and assignment made unavailable 
	//data should only belong to this object, so cannot be copied
	basic_unique_ptr(const basic_unique_ptr&) = delete;
	basic_unique_ptr& operator=(const basic_unique_ptr&) = delete;
	/*
	* Move constructor and assignment for moving data of unique_ptrs between each other
	* Allowed since in total, only one reference to the underyling object exists afterwards.
	*/
	basic_unique_ptr(basic_unique_ptr&& other) noexcept : _data(other._data) {
		other._data = nullptr;
	}
	basic_unique_ptr& operator=(basic_unique_ptr&& other) noexcept {
		if (this != &other) {
			std::swap(_data, other._data);
		}
		return *this;
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
};