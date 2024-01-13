#pragma once
#include <stdio.h>
#include <exception>
/*
* Minimal pointer wrapper. Only serves automatic resource handling.
*/
class FILE_ptr {
private:
	//Internal raw file pointer
	FILE* file;
public:
	/*
	* Constructor which attempts to open a file.
	* If opening fails, the pointer is null, so checks for that and throws appropriate exception
	*/
	FILE_ptr(const char* fn, const char* mode) : file(fopen(fn, mode)) {
		if (file == nullptr) {
			throw std::exception("file could not be opened");
		}
	}
	// closes file. Pointer is not deleted, since new was never used (here)
	~FILE_ptr() {
		fclose(file);
	}
	//Exposes underlying pointer
	FILE* get() {
		return file;
	}
};