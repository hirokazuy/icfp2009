// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_HOHMANN_CONTROLLER_HPP__
#define __CTRL_HOHMANN_CONTROLLER_HPP__

#include "controller_base.hpp"
#include "vector2d.hpp"

class HohmannController : public ControllerBase {
public:
	static const double G;
	static const double M;

public:
	HohmannController();
	virtual ~HohmannController();

	virtual int update(boost::shared_ptr<ObfVM> vm);

protected:
	void updateEnv(boost::shared_ptr<ObfVM> vm);
	Vector2D<double> calculateDeltaV1();
	Vector2D<double> calculateDeltaV2();
	void updateVector(boost::shared_ptr<ObfVM> vm, Vector2D<double> v);

private:
	double score_;
	double fuel_;
	Vector2D<double> vec_;
	Vector2D<double> prevVec_;
	double initradius_;
	double radius_;
	Vector2D<double> velocity_;
	unsigned int step_;
};

#endif // __CTRL_HOHMANN_CONTROLLER_HPP__
