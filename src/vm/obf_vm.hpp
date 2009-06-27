// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_OBF_VM_HPP__
#define __VM_OBF_VM_HPP__

#include <istream>
#include <ostream>
#include <vector>

class ObfFrame;

class ObfVM
{
public:
	typedef unsigned int instruction_t;
	typedef std::vector<instruction_t> instructions_t;

	typedef double memorydata_t;
	typedef std::vector<memorydata_t> memory_t;

public:
	ObfVM() {}
	~ObfVM() {}

	int load(std::istream& stream);

	void addFrame(const ObfFrame& frame);

	void dump(std::ostream& stream);

private:
	void dumpOperator(std::ostream& stream);
	void dumpMemory(std::ostream& stream);

private:
	instructions_t operators_;
	memory_t memory_;
};

#endif // __VM_OBF_VM_HPP__
