// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __MODEL_HOHMANN_MODEL_HPP__
#define __MODEL_HOHMANN_MODEL_HPP__

#include <boost/shared_ptr.hpp>
#include "../common/vector2d.hpp"
#include "model.hpp"

class ObfVM;

class HohmannModel : public Model {
public:
	typedef Vector2D<double> vector_t;

public:
	static const double G;
	static const double M;

public:
	HohmannModel();
	virtual ~HohmannModel();

	virtual void updateEnv(boost::shared_ptr<ObfVM> vm);
	virtual void draw();

	double getScore();
	double getFuel();
	vector_t& getRelative();
	vector_t& getPrevRelative();
	vector_t& getVelocity();
	double getTargetRadius();

protected:
	void drawSatellite();
	void drawEarth();

private:
	double score_;
	double fuel_;
	Vector2D<double> vec_;
	Vector2D<double> prevVec_;
	double radius_;
	Vector2D<double> velocity_;
	unsigned int step_;
};

#endif
