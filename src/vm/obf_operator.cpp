// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "obf_operator.hpp"

static DtypeOp getDtypeOpValue(unsigned int instruction) {
	return static_cast<DtypeOp>(instruction >> 28);
}

static short getDtypeR1Value(unsigned int instruction) {
	return static_cast<short>((instruction >> 14) & 0x3fff);
}

static short getDtypeR2Value(unsigned int instruction) {
	return static_cast<short>(instruction & 0x3fff);
}

static StypeOp getStypeOpValue(unsigned int instruction) {
	return static_cast<StypeOp>((instruction >> 24) & 0x0f);
}

static short getStypeR1Value(unsigned int instruction) {
	return static_cast<short>(instruction & 0x3fff);
}

static short getStypeImmValue(unsigned int instruction) {
	return static_cast<short>((instruction >> 14) & 0x01ff);
}

static ObfOps* decodeDtype(unsigned int instruction) {
	DtypeOps *op = new DtypeOps;
	op->type = DType;
	op->ops = getDtypeOpValue(instruction);
	op->r1 = getDtypeR1Value(instruction);
	op->r2 = getDtypeR2Value(instruction);
	return op;
}

static ObfOps* decodeStype(unsigned int instruction) {
	StypeOps *op = new StypeOps;
	op->type = SType;
	op->ops = getStypeOpValue(instruction);
	op->imm = getStypeImmValue(instruction);
	op->r1 = getStypeR1Value(instruction);
	return op;
}

boost::shared_ptr<ObfOps> decode(unsigned int instruction) {
	ObfOps* ret = NULL;
	DtypeOp ops = getDtypeOpValue(instruction);
	if (ops == None) {
		// S-Type operator
		ret = decodeStype(instruction);
	} else {
		// D-Type operator
		ret = decodeDtype(instruction);
	}
	return boost::shared_ptr<ObfOps>(ret);
}

CmpzType decodeCmpzType(unsigned int imm) {
	return static_cast<CmpzType>( imm >> 7 );
}


static const char *OpsTypeName[] = {
	"D-Type", "S-Type",
};

static const char *DtypeOpName[] = {
	"None", "Add", "Sub", "Mult", "Div", "Output", "Phi",
};

static const char *StypeOpName[] = {
	"Noop", "Cmpz", "Sqrt", "Copy", "Input",
};

std::ostream& ObfOps::dump(std::ostream& os) {
	os << OpsTypeName[type];
	return os;
}

std::ostream& DtypeOps::dump(std::ostream& os) {
	ObfOps::dump(os) << ",";
	os << DtypeOpName[ops];
	os << "(" << std::hex << static_cast<int>(r1) << ", "
	   << std::hex << static_cast<int>(r2) << ")";
	return os;
}

std::ostream& StypeOps::dump(std::ostream& os) {
	ObfOps::dump(os) << ",";
	os << StypeOpName[ops] << "<" << imm << ">,(" << r1 << ")";
	return os;
}
