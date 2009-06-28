// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_INPUT_PORT_HPP__
#define __VM_INPUT_PORT_HPP__

#include "mapped_port.hpp"

class InputPort : public MappedPort
{
public:
	enum { CONFIG_PORT = 0x3e80, };
public:
	InputPort(size_t size);
	virtual ~InputPort();

	virtual double& operator[](size_t idx);
	virtual size_t size();
};

#endif // __VM_INPUT_PORT_HPP__
