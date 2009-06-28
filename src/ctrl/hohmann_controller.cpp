// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "hohmann_controller.hpp"
#include "../vm/obf_vm.hpp"
#include "../vm/mapped_port.hpp"
#include <iostream>

const double HohmannController::G = 6.67428e-11;
const double HohmannController::M = 6.0e+24;

HohmannController::HohmannController()
	: score_(0.0), fuel_(0.0), vec_(0.0, 0.0), prevVec_(0.0, 0.0),
	  initradius_(0.0), radius_(0.0), velocity_(0.0, 0.0), step_(0)
{}

HohmannController::~HohmannController() {
}

int HohmannController::update(boost::shared_ptr<ObfVM> vm) {
	++step_;

	updateEnv(vm);
	if (step_ == 1) {
		return 0;
	}

	Vector2D<double> deltaV1 = calculateDeltaV1();
	Vector2D<double> deltaV2 = calculateDeltaV2();
	std::cout << "step: " << std::dec << step_ << std::endl;
	std::cout << "prev: " << velocity_ << std::endl;
	std::cout << "next1: " << deltaV1 << std::endl;
	std::cout << "next2: " << deltaV2 << std::endl;

	Vector2D<double> nextVel = deltaV1;
	if (step_ > 2) {
		nextVel *= 0;
		updateVector(vm, nextVel);
		return 0;
	}
	if (step_ > 500) {
		nextVel = deltaV2;
	}
//	nextVel *= 10 / nextVel.length();

	updateVector(vm, nextVel);

	std::cout << "velocity: " << nextVel << std::endl;
	return 0;
}

void HohmannController::updateEnv(boost::shared_ptr<ObfVM> vm) {
	MappedPort& outPort = vm->getOutputPort();
	prevVec_ = vec_;

	score_ = outPort[0];
	fuel_ = outPort[1];
	vec_.setX(outPort[2]);
	vec_.setY(outPort[3]);
	radius_ = outPort[4];
	if (step_ == 0) {
		initradius_ = vec_.length();
	}

	velocity_ = vec_ - prevVec_;
	std::cout << "now velocity: " << velocity_ << std::endl;
}

Vector2D<double> HohmannController::calculateDeltaV1() {
	double r1 = vec_.length();
	double r2 = radius_;
	std::cout << "diff: " << r2 - r1 << std::endl;

	double v = ::sqrt(G*M/r1) * (::sqrt((2 * r2) / (r1 + r2)) - 1);
	Vector2D<double> normVec = vec_.norm();
	Vector2D<double> normVel = velocity_.norm();
	normVel = Vector2D<double>(normVel.getY(), normVel.getX());

	return velocity_ + (normVel * v);
}

Vector2D<double> HohmannController::calculateDeltaV2() {
	double r1 = vec_.length();
	double r2 = radius_;

	double v = ::sqrt(G*M/r2) * ( 1 - ::sqrt((2 * r1) / (r1 + r2)) );
	Vector2D<double> normVec = vec_.norm();
	Vector2D<double> normVel = velocity_.norm();
	normVel = Vector2D<double>(-normVel.getY(), -normVel.getX());

	return normVel * v;
}

void HohmannController::updateVector(boost::shared_ptr<ObfVM> vm, Vector2D<double> v) {
	MappedPort& inPort = vm->getInputPort();
	inPort[2] = v.getX();
	inPort[3] = v.getY();
}
