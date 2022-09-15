.PHONY: dirs clean

CXXFLAGS = -Wfatal-errors
SRC = $(shell ls src/*.h)
TEST = $(shell ls test/*.h)

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++14 $< -o $@ -lgtest -pthread $(CXXFLAGS)

test: all
	bin/ut_all

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
