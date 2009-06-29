// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "command.hpp"
#include "../vm/input_port.hpp"

Command::Command(unsigned int step) : step_(step) {}

Command::~Command() {}

void Command::append(unsigned int addr, double value) {
	PortInput pin;
	pin.addr = addr;
	pin.value = value;
	inputs_.push_back(pin);
}

size_t Command::length() {
	return inputs_.size();
}

static void writeInt(std::ostream& os, unsigned int val) {
	os.write(reinterpret_cast<char*>(&val), sizeof(unsigned int));
}

static void writeDouble(std::ostream& os, double val) {
	os.write(reinterpret_cast<char*>(&val), sizeof(double));
}

void Command::write(std::ostream& os) {
	writeInt(os, step_);
	writeInt(os, inputs_.size());

	for (int i = 0; i < inputs_.size(); ++i) {
		PortInput& p = inputs_[i];
		writeInt(os, p.addr);
		writeDouble(os, p.value);
	}
}
