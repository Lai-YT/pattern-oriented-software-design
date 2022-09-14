.PHONY: dirs clean

CXXFLAGS = -Wfatal-errors
SRC = src/point.h src/two_dimensional_vector.h src/circle.h src/triangle.h src/shape.h src/rectangle.h
TEST = test/ut_point.h test/ut_two_dimensional_vector.h test/ut_circle.h \
	test/ut_triangle.h test/ut_rectangle.h

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++11 $< -o $@ -lgtest -pthread $(CXXFLAGS)

test: all
	bin/ut_all

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
