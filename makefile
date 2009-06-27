# -*- Mode: makefile; Coding: utf-8; tab-width: 4; -*-
TARGET = simulator

SRCS = src/main.cpp src/vm/obf_vm.cpp src/vm/obf_operator.cpp
OBJS = $(patsubst %.cpp, %.o, ${SRCS})

CXXFLAGS = -g -O0 -Wall

.PHONY: all clean

all: ${TARGET}

clean:
	-${RM} ${OBJS} ${TARGET}

src/%.o: src/%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o ${TARGET} ${OBJS} ${LIBS}

src/main.o: src/main.cpp src/vm/obf_vm.hpp
src/vm/obf_vm.o: src/vm/obf_vm.cpp src/vm/obf_vm.hpp src/vm/obf_reader.hpp
src/vm/obf_operator.o: src/vm/obf_operator.cpp src/vm/obf_operator.hpp
