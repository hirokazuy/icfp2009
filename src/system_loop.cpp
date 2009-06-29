// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include <iostream>
#include <fstream>

#include "system_loop.hpp"
#include "window/window.hpp"
#include "vm/obf_vm.hpp"
#include "ctrl/hohmann_controller.hpp"
#include "ctrl/command_set.hpp"
#include "model/model.hpp"

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

template <typename T>
static void write(std::ostream& os, T val) {
	os.write(reinterpret_cast<char*>(&val), sizeof(T));
}

bool SystemLoop::init(int argc, char *argv[]) {
	window_ = boost::shared_ptr<SDLWindow>(new GLSDLWindow());
	window_->init();

	config_ = atoi(argv[2]);
	vm_ = boost::shared_ptr<ObfVM>(new ObfVM());
	initVM((*vm_), argv[1]);

	vm_->dump(std::cout);
	controller_ = boost::shared_ptr<ControllerBase>(new HohmannController());
	controller_->init(vm_, config_);
	model_ = controller_->getModel();

	return true;
}

int SystemLoop::doLoop()
{
	SDL_Event evt;
	bool running = true;
	while (running) {
		for (int i = 0; i < 100; ++i) {
			if (controller_->update(vm_)) {
				running = false;
				break;
			}
			vm_->execute();
//			vm_->dump(std::cout);
//			std::cout << *vm_ << std::endl;
		}
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
		SDL_Delay(1);
	}
	std::ofstream out("out.dat", std::fstream::out | std::fstream::binary);
	write<unsigned int>(out, 0xCAFEBABE);
	write<unsigned int>(out, 604);
	write<unsigned int>(out, config_);
	controller_->getCommandSet()->write(out);
	out.close();
	return 0;
}

void SystemLoop::draw() {
	window_->clear();

	model_->draw();

	window_->swapBuffers();
}
