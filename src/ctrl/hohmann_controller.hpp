// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __CTRL_HOHMANN_CONTROLLER_HPP__
#define __CTRL_HOHMANN_CONTROLLER_HPP__

#include "controller_base.hpp"
#include "../common/vector2d.hpp"

class HohmannModel;

class HohmannController : public ControllerBase {
public:
	static const double G;
	static const double M;

	enum Mode {
		UNINIT, INIT, START, ACCELL, BRAKE,  END, STAY,
	};

public:
	HohmannController();
	virtual ~HohmannController();

	virtual void init(boost::shared_ptr<ObfVM> vm, double config);
	virtual Model* getModel();
	virtual CommandSet* getCommandSet();
	virtual int update(boost::shared_ptr<ObfVM> vm);

protected:
	void calculateNextVector(boost::shared_ptr<ObfVM> vm);
	void updateEnv(boost::shared_ptr<ObfVM> vm);
	Vector2D<double> calculateDeltaV1();
	Vector2D<double> calculateDeltaV2();
	double calculateStayV();
	void updateVector(boost::shared_ptr<ObfVM> vm, Vector2D<double> v);

private:
	HohmannModel *model_;
	CommandSet *commands_;
	unsigned int step_;
	double initRadius_;
	Vector2D<double> deltaV1_;
	Vector2D<double> deltaV2_;
	Mode mode_;
};

#endif // __CTRL_HOHMANN_CONTROLLER_HPP__
