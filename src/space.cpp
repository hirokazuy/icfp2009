// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "space.hpp"

#include "earth.hpp"
#include "satellite.hpp"
#include "vm/obf_vm.hpp"

int Space::update(boost::shared_ptr<ObfVM> vm) {
	satellite_->update(vm);
	return 0;
}

int Space::draw() {
}
