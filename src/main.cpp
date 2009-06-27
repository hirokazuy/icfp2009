//------------------------------------------------------------------------------
// main インプリメント
// Last Modified: 2009/06/27 10:52:57
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>

#include "vm/obf_vm.hpp"

void printUsage() {
	std::cout << "usage: simulator obf" << std::endl;
}

void loadFromFile(ObfVM& vm, char *filename) {
	std::fstream stream(filename, std::fstream::in | std::fstream::binary);
	vm.load(stream);
	stream.close();
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printUsage();
		return 0;
	}

	ObfVM vm;
	loadFromFile(vm, argv[1]);

	return 0;
}
