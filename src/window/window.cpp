// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include "window.hpp"

//-------------------------------------------------------------------------------
// SDL Window 実装部
const SDLWindow::SDLWindowInitOption SDLWindow::DEFAULT_INIT_OPT = {
	600, 480,
	16,
	SDL_DOUBLEBUF,
};

SDLWindow::SDLWindow()
	: window_(0)
{
}

SDLWindow::~SDLWindow()
{
}

bool SDLWindow::init(const SDLWindowInitOption& opt)
{
	window_ = SDL_SetVideoMode(opt.width, opt.height, opt.depth, opt.flags);
	if (!window_) {
		// error
		std::cerr << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return false;
	}
	opt_ = opt;

	return true;
}

bool SDLWindow::caption(const std::string& wmName, const std::string& iconName)
{
	SDL_WM_SetCaption(wmName.c_str(), iconName.c_str());
	return true;
}

void SDLWindow::clear() {
}

void SDLWindow::swapBuffers() {
	SDL_GL_SwapBuffers();
}


//-------------------------------------------------------------------------------
// GLSDLWindow 実装部
bool GLSDLWindow::init(const SDLWindowInitOption& opt)
{
	// 各カラー用のサイズ指定
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	// カラーデプスサイズ
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	// Double buffer 有効
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// SDL のオプションに SDL_OPENGL を追加して初期化
	SDLWindowInitOption o = opt;
	o.flags |= SDL_OPENGL;
	SDLWindow::init(o);

	float ratio = static_cast<float>(o.width) / o.height;
	glShadeModel( GL_SMOOTH );
	glClearColor(0, 0, 0, 0);

//	glCullFace( GL_BACK );
//	glFrontFace( GL_CCW );
//	glEnable( GL_CULL_FACE );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, ratio, 1, 10);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, o.width, o.height);

	return true;
}

void GLSDLWindow::clear() {
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
