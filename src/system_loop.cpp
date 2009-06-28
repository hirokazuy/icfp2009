// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include <iostream>
#include <fstream>

#include "system_loop.hpp"
#include "window/window.hpp"
#include "vm/obf_vm.hpp"
#include "ctrl/hohmann_controller.hpp"

SystemLoop::SystemLoop() {}
SystemLoop::~SystemLoop() {}

static void loadFromFile(ObfVM& vm, char *filename) {
	std::fstream stream(filename, std::fstream::in | std::fstream::binary);
	vm.load(stream);
	stream.close();
}

static void initVM(ObfVM& vm, char *filename) {
	loadFromFile(vm, filename);
}

bool SystemLoop::init(int argc, char *argv[]) {
	window_ = boost::shared_ptr<SDLWindow>(new GLSDLWindow());
	window_->init();

	vm_ = boost::shared_ptr<ObfVM>(new ObfVM());
	initVM((*vm_), argv[1]);

	vm_->dump(std::cout);
	vm_->setConfig(1001);
	vm_->execute();
	controller_ = boost::shared_ptr<ControllerBase>(new HohmannController());

	return true;
}

int SystemLoop::doLoop()
{
	SDL_Event evt;
	bool running = true;
	while (running) {
		controller_->update(vm_);
		vm_->execute();
		std::cout << *vm_ << std::endl;
		draw();
		while (SDL_PollEvent(&evt)) {
			switch (evt.type) {
//                      case SDL_KEYDOWN:
			case SDL_KEYUP:
				break;
			case SDL_MOUSEBUTTONDOWN:
//				mouseEventDispatch(evt);
				break;
			case SDL_QUIT:
				running = false;
				break;
			}
		}
		SDL_Delay(20);
		vm_->setConfig(0);
	}
	return 0;
}

void SystemLoop::draw() {
	window_->clear();

	window_->swapBuffers();
}
