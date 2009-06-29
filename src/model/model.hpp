// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <boost/shared_ptr.hpp>

class ObfVM;

class Model {
public:
	Model() {}
	virtual ~Model() {}

	virtual void updateEnv(boost::shared_ptr<ObfVM> vm) = 0;
	virtual void draw() = 0;
};

#endif // __MODEL_HPP__
