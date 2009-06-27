// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __SPACE_HPP__
#define __SPACE_HPP__

#include <boost/shared_ptr.hpp>

class Earth;
class Satellite;
class ObfVM;

class Space {
public:
	Space();
	~Space();

	int update(boost::shared_ptr<ObfVM> vm);
	int draw();

private:
	boost::shared_ptr<Earth> earth_;
	boost::shared_ptr<Satellite> satellite_;
};

#endif // __SPACE_HPP__
