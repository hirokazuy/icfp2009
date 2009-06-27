// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "earth.hpp"

Earth::Earth() : mass_(0), radius_(6.357*100000) {
}

Earth::~Earth() {}

double Earth::getMass() { return mass_; }
double Earth::getRadius() { return radius_; }
