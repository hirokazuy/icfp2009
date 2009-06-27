// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_OBF_VM_HPP__
#define __VM_OBF_VM_HPP__

#include <istream>
#include <ostream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "mapped_port.hpp"

class ObfFrame;
struct ObfOps;
struct StypeOps;
struct DtypeOps;

class ObfVM
{
public:
	typedef unsigned int instruction_t;
	typedef std::vector<instruction_t> instructions_t;

	typedef double memorydata_t;
	typedef std::vector<memorydata_t> memory_t;

public:
	ObfVM();
	~ObfVM() {}

	int load(std::istream& stream);

	void addFrame(const ObfFrame& frame);

	void setConfig(unsigned int config);
	MappedPort& getInputPort();
	MappedPort& getOutputPort();

	void dump(std::ostream& stream);

	int execute();
	void update() {}

private:
	void dispatch(boost::shared_ptr<ObfOps> op);
	void executeStypeOps(StypeOps* op);
	void executeDtypeOps(DtypeOps* op);

	void dumpOperator(std::ostream& stream);
	void dumpMemory(std::ostream& stream);

private:
	instructions_t operators_;
	memory_t memory_;
	MappedPort input_;
	MappedPort output_;
	int status_;

	friend std::ostream& operator<<(std::ostream& os, ObfVM& vm);
};

std::ostream& operator<<(std::ostream& os, ObfVM& vm);

#endif // __VM_OBF_VM_HPP__
