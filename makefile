.PHONY: dirs clean

SRC = src/point.h
TEST = test/ut_point.h

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++11 $< -o $@ -lgtest -pthread

dirs:
	mkdir -p bin

clean:
	rm bin/*
