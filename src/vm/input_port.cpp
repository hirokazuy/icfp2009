// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "input_port.hpp"

InputPort::InputPort(size_t size) : MappedPort(size+1) {
}

InputPort::~InputPort() {}

double& InputPort::operator[](size_t idx) {
	if (idx == CONFIG_PORT) {
		return MappedPort::operator[]( size() );
	} else {
		return MappedPort::operator[]( idx );
	}
}

size_t InputPort::size() {
	return MappedPort::size() - 1;
}
