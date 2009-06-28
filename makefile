# -*- Mode: makefile; Coding: utf-8; tab-width: 4; -*-
TARGET = simulator

SRCS = src/main.cpp src/system_loop.cpp \
		src/space.cpp src/earth.cpp src/satellite.cpp \
		src/vm/obf_vm.cpp src/vm/obf_operator.cpp \
		src/vm/mapped_port.cpp src/vm/input_port.cpp \
		src/window/window.cpp src/window/sdl.cpp \
		src/ctrl/hohmann_controller.cpp
OBJS = $(patsubst %.cpp, %.o, ${SRCS})

CXXFLAGS = -g -O0 -Wall
LIBS = -lSDL -lGL -lGLU

.PHONY: all clean

all: ${TARGET}

clean:
	-${RM} ${OBJS} ${TARGET}

src/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o ${TARGET} ${OBJS} ${LIBS}

src/main.o: src/main.cpp src/window/sdl.hpp src/system_loop.hpp
src/system_loop.o: src/system_loop.cpp src/system_loop.hpp \
  src/window/window.hpp src/vm/obf_vm.hpp

src/vm/obf_vm.o: src/vm/obf_vm.cpp src/vm/obf_vm.hpp src/vm/obf_reader.hpp \
  src/vm/obf_operator.hpp
src/vm/obf_operator.o: src/vm/obf_operator.cpp src/vm/obf_operator.hpp

src/window/sdl.o: src/window/sdl.cpp
src/window/window.o: src/window/window.cpp src/window/window.hpp

