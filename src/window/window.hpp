// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <SDL/SDL.h>
#include <boost/utility.hpp>

//-------------------------------------------------------------------------------
// SDL_Window の定義
//-------------------------------------------------------------------------------
class SDLWindow : public boost::noncopyable
{
public:
	struct SDLWindowInitOption
	{
		unsigned int width;
		unsigned int height;
		Uint32 depth;
		Uint32 flags;
	};
	static const SDLWindowInitOption DEFAULT_INIT_OPT;

public:
	SDLWindow();
	virtual ~SDLWindow();

	virtual bool init(const SDLWindowInitOption& opt = DEFAULT_INIT_OPT);
	bool caption(const std::string& wmName, const std::string& iconName);
	virtual void clear();
	virtual void swapBuffers();

private:
	SDL_Surface *window_;
	SDLWindowInitOption opt_;
};


//-------------------------------------------------------------------------------
// OpenGL 対応版 Window
//-------------------------------------------------------------------------------
class GLSDLWindow : public SDLWindow
{
public:
	GLSDLWindow() {}
	virtual ~GLSDLWindow() {}

	bool init(const SDLWindowInitOption& opt);
	void clear();
};


#endif // __WINDOW_HPP__
