#pragma once
#include <algorithm>
#include <vector>
#include <iostream>
template<class T>
class generic_wrapper {
private:
	T* _data;
public:
	generic_wrapper(const generic_wrapper& g) = delete;
	generic_wrapper(generic_wrapper&& g) {
		_data = g._data;
		g._data = nullptr;
	}
	generic_wrapper& operator=(const generic_wrapper& g) = delete;
	generic_wrapper& operator=(generic_wrapper&& g){
		if (_data != nullptr) {
			delete _data;
		}
		_data = g._data;
		g._data == nullptr;
		return *this;
	}

	template<class... Args>
	generic_wrapper(Args... args) {
		_data = new T(args...);
	}
	template<class... Args>
	static generic_wrapper<T> make_wrapped(Args... args) {
		generic_wrapper<T> t(args...);
		return t;
	}
	~generic_wrapper() {
		delete _data;
	}
	T* expose() {
		return _data;
	}

};