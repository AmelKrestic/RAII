#pragma once
#include <algorithm>
#include <vector>
#include <iostream>
template<class T>
class generic_wrapper {
private:
	T* _data; //Object held by the Wrapper
public:
	/*
	* Copy assignment and constructor disallowed.
	* Guarantees that Object can only be held by this wrapper
	*/
	generic_wrapper(const generic_wrapper& g) = delete;
	generic_wrapper& operator=(const generic_wrapper& g) = delete;

	/*
	* Move constructor.
	* Move Object from other wrapper to this one.
	*/
	generic_wrapper(generic_wrapper&& g) noexcept {
		_data = g._data;
		g._data = nullptr;
	}
	/*
	* Move assignment.
	* Swap contents of wrappers.
	*/
	generic_wrapper& operator=(generic_wrapper&& g) noexcept{
		std::swap(_data, g._data);
		return *this;
	}
	/*
	* Constructor with parameter forwarding.
	* Creates an object of given type using parameter list args.
	* This way no pointer can be given to the wrapper only to be changed later
	* and no new operator has to be used in the parameter list.
	*/
	template<class... Args>
	generic_wrapper(Args... args) {
		_data = new T(args...);
	}
	/*
	* Static method for creating Wrapper.
	* Same as the above, but avoids using new entirely when creating a wrapper.
	* If above constructor was private, there would be no regular public constructors
	* removing the need for raw new uses.
	*/
	template<class... Args>
	static generic_wrapper<T> make_wrapped(Args... args) {
		return generic_wrapper<T>(args...);
	}
	/*
	* Destructor.
	* Destroys underlying object, if it exists.
	*/
	~generic_wrapper() {
		if (_data != nullptr) {
			delete _data;
		}
		std::cout << "wrapper destructor" << std::endl;
	}
	/*
	* Generally not a good idea to directly expose the pointer, but here for ease of use.
	* Instead, one could override (->) operator to return the underlying object instead of the pointer.
	*/
	T* expose() {
		return _data;
	}

};