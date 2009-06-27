// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include "sdl.hpp"
#include <SDL/SDL.h>

int SDL::init() {
	return SDL_Init(SDL_INIT_VIDEO);
}

const char* SDL::getError() {
	return SDL_GetError();
}
