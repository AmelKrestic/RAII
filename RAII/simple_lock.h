#pragma once
template<class Mutex>
class simple_lock {
private:
	//Mutex to lock
	Mutex& _m;
public:
	//Constructor and destructor simply lock and unlock the mutex.
	simple_lock(Mutex& m) : _m(m) {
		_m.lock();
	}
	~simple_lock() {
		_m.unlock();
	}
	// Here one could additionally implement funktionality like prematurely unlocking a mutex,
	// etc.
};