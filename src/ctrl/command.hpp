// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_COMMAND_HPP__
#define __CTRL_COMMAND_HPP__

#include <vector>
#include <ostream>

class InputPort;

class Command {
public:
	struct PortInput {
		unsigned int addr;
		double value;
	};

public:
	Command(unsigned int step);
	virtual ~Command();

	void append(unsigned int addr, double value);
	size_t length();
	unsigned int getStep() { return step_; }

	void write(std::ostream& os);

private:
	unsigned int step_;
	std::vector<PortInput> inputs_;
};

#endif // __CTRL_COMMAND_HPP__
