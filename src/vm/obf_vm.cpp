// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "obf_vm.hpp"
#include "obf_reader.hpp"

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

void ObfVM::dump() {
	dumpOperator();
	dumpMemory();
}

void ObfVM::dumpOperator() {
		
}

void ObfVM::dumpMemory() {}
