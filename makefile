# -*- Mode: makefile; Coding: utf-8; tab-width: 4; -*-
TARGET = simulator

SRCS = src/main.cpp
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
