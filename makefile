.PHONY: dirs clean

SRC = src/point.h src/two_dimensional_vector.h src/circle.h
TEST = test/ut_point.h test/ut_two_dimensional_vector.h test/ut_circle.h

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++11 $< -o $@ -lgtest -pthread

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
