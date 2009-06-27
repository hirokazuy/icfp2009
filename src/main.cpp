//------------------------------------------------------------------------------
// main インプリメント
// Last Modified: 2009/06/27 10:52:57
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "window/sdl.hpp"
#include "system_loop.hpp"

void printUsage() {
	std::cout << "usage: simulator obf" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printUsage();
		return 0;
	}

	if (SDL::init() == -1) {
		std::cout << "SDL_Init error: " << SDL::getError() << std::endl;
		return 0;
	}

	boost::shared_ptr<SystemLoop> loop(new SystemLoop());
	loop->init(argc, argv);

	return loop->doLoop();
}
