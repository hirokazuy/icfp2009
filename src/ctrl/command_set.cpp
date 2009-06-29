// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "command_set.hpp"
#include "../vm/obf_vm.hpp"
#include "../vm/mapped_port.hpp"

CommandSet::CommandSet() : commands_(), prevX(-1.0),
						   prevY(-1.0), prevConf(-1.0)
{}

CommandSet::~CommandSet() {}

void CommandSet::appendLast(unsigned int step) {
	command_t com = command_t(new Command(step));
	commands_.push_back(com);
}

int CommandSet::update(unsigned int step, boost::shared_ptr<ObfVM> vm) {
	command_t com = command_t(new Command(step));

	MappedPort& input = vm->getInputPort();
	if (prevX != input[2]) {
		prevX = input[2];
		com->append(2, input[2]);
	}
	if (prevY != input[3]) {
		prevY = input[3];
		com->append(3, input[3]);
	}
	if (prevConf != input[0x3e80]) {
		prevConf = input[0x3e80];
		com->append(0x3e80, input[0x3e80]);
	}
	if (com->length() != 0) {
		commands_.push_back(com);
	}
	return com->length();
}

int CommandSet::write(std::ostream& os) {
	for (int i = 0; i < commands_.size(); ++i) {
		command_t com = commands_[i];
		com->write(os);
	}
}
