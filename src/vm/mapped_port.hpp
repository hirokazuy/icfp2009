// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_MAPPED_PORT_HPP__
#define __VM_MAPPED_PORT_HPP__

#include <vector>

class MappedPort
{
public:
	MappedPort(size_t size);
	~MappedPort();

	double& operator[](size_t idx);
	size_t size();

private:
	std::vector<double> values_;
};

#endif // __VM_MAPPED_PORT_HPP__
