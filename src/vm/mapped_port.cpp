// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "mapped_port.hpp"

MappedPort::MappedPort(size_t size) : values_(size) {
}

MappedPort::~MappedPort() {
}

double& MappedPort::operator[](size_t idx) {
	return values_[idx];
}

size_t MappedPort::size() {
	return values_.size();
}
