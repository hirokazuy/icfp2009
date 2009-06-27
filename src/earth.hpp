// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __EARTH_HPP__
#define __EARTH_HPP__

class Earth {
public:
	Earth();
	~Earth();

	double getMass();
	double getRadius();

private:
	double mass_;
	double radius_;
};

#endif // __EARTH_HPP__
