// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_OBF_VM_HPP__
#define __VM_OBF_VM_HPP__

#include <istream>
#include <vector>

class ObfFrame;

class ObfVM
{
public:
	ObfVM() {}
	~ObfVM() {}

	int load(std::istream& stream);

	void addFrame(const ObfFrame& frame);

	void dump();
	void dumpOperator();
	void dumpMemory();

private:
	std::vector<double> memory_;
	std::vector<unsigned int> operators_;
};

#endif // __VM_OBF_VM_HPP__
