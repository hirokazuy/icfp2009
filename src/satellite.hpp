// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __SATELLITE_HPP__
#define __SATELLITE_HPP__

#include <ostream>
#include <boost/shared_ptr.hpp>

class ObfVM;

class Satellite {
public:
	Satellite();
	~Satellite();

	int update(boost::shared_ptr<ObfVM> vm);

private:
	double fuel_;
	double x_;
	double y_;

	friend std::ostream& operator << (std::ostream& os, Satellite& satellite);
};

std::ostream& operator << (std::ostream& os, Satellite& satellite);

#endif // __SATELLITE_HPP__
