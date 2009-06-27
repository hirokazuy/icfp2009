// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include <math.h>
#include <stdexcept>
#include <sstream>

#include "obf_vm.hpp"
#include "obf_reader.hpp"
#include "obf_operator.hpp"

ObfVM::ObfVM() : input_(10), output_(10), status_(0) {}

int ObfVM::load(std::istream& stream) {
	ObfReader reader(stream);
	while (true) {
		ObfFrame frame = reader.getNextFrame();
		if (reader.isEof()) break;

		addFrame(frame);
	}
	return reader.size();
}

void ObfVM::addFrame(const ObfFrame& frame) {
	operators_.push_back(frame.instruction);
	memory_.push_back(frame.data);
}

void ObfVM::setConfig(unsigned int config) {
	input_[ input_.size() - 1 ] = config;
}

MappedPort& ObfVM::getInputPort() {
	return input_;
}

MappedPort& ObfVM::getOutputPort() {
	return output_;
}


int ObfVM::execute() {
	typedef instructions_t::iterator iterator_t;
	int addr = 0;
	iterator_t end = operators_.end();
	for (iterator_t it = operators_.begin();
		 it != end; ++it, ++addr) {
		obfops_t ops = decode(*it);
		ops->addr = addr;
		dispatch(ops);
	}
	return addr;
}

void ObfVM::dispatch(obfops_t op) {
	if (op->type == SType) {
		// S-Type operator
		executeStypeOps(static_cast<StypeOps*>(&*op));
	} else if (op->type == DType) {
		// D-Type operator
		executeDtypeOps(static_cast<DtypeOps*>(&*op));
	}
}

void ObfVM::executeStypeOps(StypeOps* op) {
	memory_t& mem = memory_;
	switch (op->ops) {
	case Noop: break;
	case Cmpz:
		switch (decodeCmpzType(op->imm)) {
		case LTZ: status_ = mem[op->r1] < 0.0 ? 1 : 0; break;
		case LEZ: status_ = mem[op->r1] <= 0.0 ? 1 : 0; break;
		case EQZ: status_ = mem[op->r1] == 0.0 ? 1 : 0; break;
		case GEZ: status_ = mem[op->r1] >= 0.0 ? 1 : 0; break;
		case GTZ: status_ = mem[op->r1] > 0.0 ? 1 : 0; break;
		default:
			std::stringstream ss;
			ss << "unknown cmp op: " << op->addr;
			throw std::runtime_error(ss.str());
		}
		break;
	case Sqrt: mem[op->addr] = ::sqrt(mem[op->r1]); break;
	case Copy: mem[op->addr] = mem[op->r1]; break;
	case Input:
		if (op->r1 == 0x3e80) {
			mem[op->addr] = input_[input_.size() - 1];
		} else {
			mem[op->addr] = input_[op->r1];
		}
		break;
	default:
		throw std::runtime_error("unknown operator");
	}
}

void ObfVM::executeDtypeOps(DtypeOps* op) {
	memory_t& mem = memory_;
	switch (op->ops) {
	case Add: mem[op->addr] = mem[op->r1] + mem[op->r2]; break;
	case Sub: mem[op->addr] = mem[op->r1] - mem[op->r2]; break;
	case Mult: mem[op->addr] = mem[op->r1] * mem[op->r2]; break;
	case Div: 
		if (abs(mem[op->r2]) < 0.00000001) {
			mem[op->addr] = 0.0f;
		} else {
			mem[op->addr] = mem[op->r1] / mem[op->r2];
		}
		break;
	case Output: output_[op->r1] = mem[op->r2]; break;
	case Phi:
		if (status_ == 1) {
			mem[op->addr] = mem[op->r1];
		} else {
			mem[op->addr] = mem[op->r2];
		}
		break;
	default:
		throw std::runtime_error("unknown operator");
	}
}

std::ostream& operator<<(std::ostream& os, ObfVM& vm) {
	MappedPort& output = vm.output_;
	os << "Score: " << output[0] << "\n";
	os << "Fuel: " << output[1] << "\n";
	os << "Delta(x): " << output[2] << "\n";
	os << "Delta(y): " << output[3] << "\n";
	os << "Target: " << output[4] << "\n";
	return os;
}


//------------------------------------------------------------------------------
// for debugging 
//------------------------------------------------------------------------------
void ObfVM::dump(std::ostream& os) {
	dumpOperator(os);
	dumpMemory(os);
}

void ObfVM::dumpOperator(std::ostream& os) {
	typedef instructions_t::iterator iterator_t;
	iterator_t end = operators_.end();
	for (iterator_t it = operators_.begin();
		 it != end; ++it) {
		obfops_t ops = decode(*it);
		ops->dump(os) << "\n";
	}
}

void ObfVM::dumpMemory(std::ostream& os) {}
