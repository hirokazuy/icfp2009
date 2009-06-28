// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __SYSTEM_LOOP_HPP__
#define __SYSTEM_LOOP_HPP__

#include <boost/shared_ptr.hpp>

class ControllerBase;
class SDLWindow;
class ObfVM;

class SystemLoop
{
public:
	SystemLoop();
	virtual ~SystemLoop();

	bool init(int argc, char *argv[]);
	int doLoop();
	void draw();
//	void mouseEventDispatch(SDL_Event evt);

private:
	boost::shared_ptr<SDLWindow> window_;
	boost::shared_ptr<ObfVM> vm_;
	boost::shared_ptr<ControllerBase> controller_;
};

#endif // __SYSTEM_LOOP_HPP__
