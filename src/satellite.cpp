// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "satellite.hpp"
#include "vm/obf_vm.hpp"

Satellite::Satellite() {}
Satellite::~Satellite() {}

int Satellite::update(boost::shared_ptr<ObfVM> vm) {
	fuel_ = vm->getOutputPort()[1];
	x_ = vm->getOutputPort()[2];
	y_ = vm->getOutputPort()[3];
}

std::ostream& operator<<(std::ostream& os, Satellite& satellite) {
	os << "Satellite[" << satellite.fuel_ << "]: ";
	os << "(" << satellite.x_ << "," << satellite.y_ << ")";
	return os;
}
