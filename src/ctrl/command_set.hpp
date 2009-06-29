// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_COMMAND_SET_HPP__
#define __CTRL_COMMAND_SET_HPP__

#include <ostream>
#include <boost/shared_ptr.hpp>
#include "command.hpp"

class ObfVM;

class CommandSet {

	typedef boost::shared_ptr<Command> command_t;
public:
	CommandSet();
	~CommandSet();

	void appendLast(unsigned int step);
	int update(unsigned int step, boost::shared_ptr<ObfVM> vm);

	int write(std::ostream& os);

private:
	std::vector<command_t> commands_;
	double prevX;
	double prevY;
	double prevConf;
};

#endif // __CTRL_COMMAND_SET_HPP__
