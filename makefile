# -*- Mode: makefile; Coding: utf-8; tab-width: 4; -*-
TARGET = simulator

SRCS = src/main.cpp src/system_loop.cpp \
		src/space.cpp src/earth.cpp src/satellite.cpp \
		src/vm/obf_vm.cpp src/vm/obf_operator.cpp \
		src/vm/mapped_port.cpp src/vm/input_port.cpp \
		src/window/window.cpp src/window/sdl.cpp \
		src/ctrl/hohmann_controller.cpp src/ctrl/command_set.cpp \
		src/ctrl/command.cpp \
		src/model/hohmann_model.cpp
OBJS = $(patsubst %.cpp, %.o, ${SRCS})

CXXFLAGS = -g -O0 -Wall
LIBS = -lSDL -lGL -lGLU

.PHONY: all clean

all: ${TARGET}

clean:
	-${RM} ${OBJS} ${TARGET}

deps:
	${CXX} -MM ${SRCS}

src/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o ${TARGET} ${OBJS} ${LIBS}

src/main.o: src/main.cpp src/window/sdl.hpp src/system_loop.hpp
src/system_loop.o: src/system_loop.cpp src/system_loop.hpp \
  src/window/window.hpp src/vm/obf_vm.hpp src/vm/mapped_port.hpp \
  src/vm/input_port.hpp src/ctrl/hohmann_controller.hpp \
  src/ctrl/controller_base.hpp src/common/vector2d.hpp
src/space.o: src/space.cpp src/space.hpp src/earth.hpp src/satellite.hpp \
  src/vm/obf_vm.hpp src/vm/mapped_port.hpp src/vm/input_port.hpp
src/earth.o: src/earth.cpp src/earth.hpp
src/satellite.o: src/satellite.cpp src/satellite.hpp src/vm/obf_vm.hpp \
  src/vm/mapped_port.hpp src/vm/input_port.hpp
src/vm/obf_vm.o: src/vm/obf_vm.cpp src/vm/obf_vm.hpp src/vm/mapped_port.hpp \
  src/vm/input_port.hpp src/vm/obf_reader.hpp src/vm/obf_operator.hpp \
  src/vm/obf_memory.hpp
src/vm/obf_operator.o: src/vm/obf_operator.cpp src/vm/obf_operator.hpp
src/vm/mapped_port.o: src/vm/mapped_port.cpp src/vm/mapped_port.hpp
src/vm/input_port.o: src/vm/input_port.cpp src/vm/input_port.hpp \
  src/vm/mapped_port.hpp
src/window/window.o: src/window/window.cpp src/window/window.hpp
src/window/sdl.o: src/window/sdl.cpp src/window/sdl.hpp
src/ctrl/hohmann_controller.o: src/ctrl/hohmann_controller.cpp \
  src/ctrl/hohmann_controller.hpp src/ctrl/controller_base.hpp \
  src/common/vector2d.hpp src/ctrl/../vm/obf_vm.hpp \
  src/ctrl/../vm/mapped_port.hpp src/ctrl/../vm/input_port.hpp \
  src/ctrl/../vm/mapped_port.hpp
