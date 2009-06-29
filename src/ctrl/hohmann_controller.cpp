// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "hohmann_controller.hpp"
#include "command_set.hpp"
#include "../vm/obf_vm.hpp"
#include "../vm/mapped_port.hpp"
#include "../model/hohmann_model.hpp"
#include <iostream>
#include <float.h>

const double HohmannController::G = 6.67428e-11;
const double HohmannController::M = 6.0e+24;

HohmannController::HohmannController()
	: step_(0), mode_(UNINIT)
{
	model_ = new HohmannModel();
	commands_ = new CommandSet();
}

HohmannController::~HohmannController() {
	delete model_;
	delete commands_;
}

void HohmannController::init(boost::shared_ptr<ObfVM> vm, double config) {
	//
	vm->setConfig(config);
	vm->execute();
	commands_->update(step_++, vm);
}

Model* HohmannController::getModel() {
	return model_;
}

CommandSet* HohmannController::getCommandSet() {
	return commands_;
}

int HohmannController::update(boost::shared_ptr<ObfVM> vm) {
	std::cout << "---------------------update--------------" << std::endl;
	updateEnv(vm);
	updateVector(vm, Vector2D<double>(0.0, 0.0));
	if (mode_ == START) {
		deltaV1_ = calculateDeltaV1();
		deltaV2_ = calculateDeltaV2();
		if (model_->getRelative().length() < model_->getTargetRadius()) {
			updateVector(vm, deltaV1_);
			mode_ = ACCELL;
		} else {
			updateVector(vm, -deltaV1_);
			mode_ = BRAKE;
		}
//		++step_;
//		return 0;
	} else if (mode_ == STAY) {
		if (::fabs(model_->getRelative().length() - model_->getTargetRadius()) > 990) {
			mode_ = START;
		}
		std::cout << "here" << std::endl;
	} else if (::fabs(model_->getRelative().length() - model_->getTargetRadius()) < 8) {
		std::cout << "here" << std::endl;
		if (mode_ == ACCELL) {
			updateVector(vm, model_->getVelocity().norm() * deltaV2_.length());
		} else {
			updateVector(vm, -deltaV2_);
		}
		deltaV1_ *= 0;
		deltaV2_ *= 0;
		mode_ = END;
	}

//	calculateNextVector(vm);

	std::cout << std::dec << step_ << std::endl;
	commands_->update(step_, vm);
	if (model_->getScore() != 0.0) {
		commands_->appendLast(step_);
	}
	++step_;

	return model_->getScore() != 0.0 || step_ > 3000000;
}

void HohmannController::calculateNextVector(boost::shared_ptr<ObfVM> vm) {
	Vector2D<double> deltaV1 = calculateDeltaV1();
	Vector2D<double> deltaV2 = calculateDeltaV2();
	std::cout << "step: " << std::dec << step_ << std::endl;
	std::cout << "prev: " << model_->getVelocity() << std::endl;
	std::cout << "next1: " << deltaV1 << std::endl;
	std::cout << "next2: " << deltaV2 << std::endl << std::endl;

	Vector2D<double> nextVel = deltaV1;
//	if (step_ > 4) {
//		nextVel *= 0;
//		updateVector(vm, nextVel);
//		return 0;
//	}
	if (abs(model_->getRelative().length() - model_->getTargetRadius()) > 61000) {
		nextVel *= 0;
		updateVector(vm, nextVel);
		return;
	}
//	if (step_ > 500) {
//		nextVel = deltaV2;
//	}
	nextVel = -model_->getVelocity();
	if (nextVel.length() > 500.0)
		nextVel = nextVel.norm() * 500.0;

	if (model_->getFuel() <= 0) {
		nextVel *= 0;
		updateVector(vm, nextVel);
		return;
	}
	updateVector(vm, nextVel);

	std::cout << "velocity: " << nextVel << std::endl;
}

void HohmannController::updateEnv(boost::shared_ptr<ObfVM> vm) {
	if (mode_ == UNINIT) {
		model_->initialize(vm);
		mode_ = INIT;
	} else {
		model_->updateEnv(vm);
		if (mode_ == INIT && step_ > 1100)
			mode_ = START;
	}
}

Vector2D<double> HohmannController::calculateDeltaV1() {
	Vector2D<double> nowVector = model_->getRelative();
	double r1 = nowVector.length();
	double r2 = model_->getTargetRadius();
	std::cout << "diff: " << r2 - r1 << std::endl;

	double v = ::sqrt(G*M/r1) * (::sqrt((2 * r2) / (r1 + r2)) - 1);
//	double v = ::sqrt(G*M/r2);
	Vector2D<double> velocity = model_->getVelocity();
	Vector2D<double> normVel = velocity.norm();

	return normVel * v;
}

Vector2D<double> HohmannController::calculateDeltaV2() {
	Vector2D<double> nowVector = model_->getRelative();
	double r1 = nowVector.length();
	double r2 = model_->getTargetRadius();

	double v = ::sqrt(G*M/r2) * ( 1 - ::sqrt((2 * r1) / (r1 + r2)) );
	Vector2D<double> normVel = model_->getVelocity().norm();

	return normVel * v;
}

double HohmannController::calculateStayV() {
	double r = model_->getTargetRadius();

	return ::sqrt(G*M/r);
}

void HohmannController::updateVector(boost::shared_ptr<ObfVM> vm, Vector2D<double> v) {
	std::cout << "update velocity: " << v << std::endl;
	MappedPort& inPort = vm->getInputPort();
	inPort[2] = v.getX();
	inPort[3] = v.getY();
}
