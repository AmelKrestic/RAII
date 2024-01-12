#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
template<class T>
class basic_shared_ptr {
private:
	T* _data;
	int* _count;
	template<class... Args>
	basic_shared_ptr(Args... args) {
		_data = new T(args...);
		_count = new int(1);
	}
public:
	basic_shared_ptr() {
	}
	basic_shared_ptr(const basic_shared_ptr& g) {
		_data = g._data;
		_count = g._count;
		(*_count)++;
	}
	basic_shared_ptr(basic_shared_ptr&& g) {
		_data = g._data;
		g._data = nullptr;
		_count = g._count;
		g._count = nullptr;
		
	}
	basic_shared_ptr& operator=(const basic_shared_ptr& g) {
		return *this=basic_shared_ptr(g);
	}
	basic_shared_ptr& operator=(basic_shared_ptr&& g) {
		std::swap(_data, g._data);
		std::swap(_count, g._count);
		return *this;
	}
	template<class... Args>
	static basic_shared_ptr<T> make_shared(Args... args) {
		basic_shared_ptr<T> t(args...);
		return t;
	}
	~basic_shared_ptr() {
		if (_data != nullptr) {
			(*_count)--;
			std::cout << "count now:" << *_count << std::endl;
			if (*_count == 0) {
				delete _data;
				delete _count;
				std::cout << "deleted" << std::endl;
			}
		}
	}
	T* expose() {
		return _data;
	}
	int count() const {
		if (_count == nullptr) {
			return 0;
		}
		return *_count;
	}
};