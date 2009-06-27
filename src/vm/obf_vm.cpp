// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "obf_vm.hpp"
#include "obf_reader.hpp"
#include "obf_operator.hpp"

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
