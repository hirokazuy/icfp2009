// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_OBF_OPERATOR_HPP__
#define __VM_OBF_OPERATOR_HPP__

#include <ostream>
#include <boost/shared_ptr.hpp>

enum OpsType {
	DType, SType,
};

struct ObfOps {
	OpsType type;

	virtual std::ostream& dump(std::ostream& os);
};

// D-Type Operator
enum DtypeOp {
	None = 0, Add = 1, Sub, Mult, Div, Output, Phi,
};

struct DtypeOps: ObfOps {
	DtypeOp ops;
	short r1;
	short r2;

	virtual std::ostream& dump(std::ostream& os);
};

// S-Type Operator
enum StypeOp {
	Noop, Cmpz, Sqrt, Copy, Input,
};

struct StypeOps: ObfOps {
	StypeOp ops;
	short imm;
	short r1;

	virtual std::ostream& dump(std::ostream& os);
};

typedef boost::shared_ptr<ObfOps> obfops_t;
obfops_t decode(unsigned int instruction);

#endif // __VM_OBF_OPERATOR_HPP__
