// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_OBF_MEMORY_HPP__
#define __VM_OBF_MEMORY_HPP__

#include <vector>

template<typename T>
class ObfMemory {
public:
	typedef typename std::vector<T>::iterator iterator;

public:
	ObfMemory() {}
	ObfMemory(size_t size) : physicalMemory_(size) {}
	~ObfMemory() {}

	T& operator[](size_t idx) {
		if (idx > physicalMemory_.capacity()) {
			resize(idx + 1);
		}
		return physicalMemory_[idx];
	}

	size_t resize(size_t size) {
		size_t oldSize = physicalMemory_.size();
		physicalMemory_.resize(size);
		return oldSize;
	}

	void push_back(T val) {
		physicalMemory_.push_back(val);
	}

	iterator begin() {
		return physicalMemory_.begin();
	}

	iterator end() {
		return physicalMemory_.end();
	}

private:
	std::vector<T> physicalMemory_;
};

#endif // __VM_OBF_MEMORY_HPP__
