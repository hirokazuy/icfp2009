// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_CONTROLLER_BASE_HPP__
#define __CTRL_CONTROLLER_BASE_HPP__

#include <boost/shared_ptr.hpp>

class ObfVM;

class ControllerBase {
public:
	ControllerBase() {}
	virtual ~ControllerBase() {}

	virtual int update(boost::shared_ptr<ObfVM> vm) = 0;
};

#endif // __CTRL_CONTROLLER_BASE_HPP__
