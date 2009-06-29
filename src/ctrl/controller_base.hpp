// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_CONTROLLER_BASE_HPP__
#define __CTRL_CONTROLLER_BASE_HPP__

#include <boost/shared_ptr.hpp>

class Model;
class ObfVM;
class CommandSet;

class ControllerBase {
public:
	ControllerBase() {}
	virtual ~ControllerBase() {}

	virtual void init(boost::shared_ptr<ObfVM> vm, double config) = 0;
	virtual Model* getModel() = 0;
	virtual CommandSet* getCommandSet() = 0;
	virtual int update(boost::shared_ptr<ObfVM> vm) = 0;
};

#endif // __CTRL_CONTROLLER_BASE_HPP__
