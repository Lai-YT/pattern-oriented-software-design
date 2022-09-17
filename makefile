.PHONY: dirs clean

CXXFLAGS = -Wfatal-errors
SRC = $(shell ls src/*.h)
TEST = $(shell ls test/*.h)

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++14 $< -o $@ -lgtest -pthread $(CXXFLAGS)

test: all
	bin/ut_all

CXXFLAGS += -fprofile-arcs -ftest-coverage -O0 -fno-inline -fno-elide-constructors
GCOVR_FLAGS = --exclude-function-lines --cobertura coverage.xml
coverage: test
	gcovr $(GCOVR_FLAGS)

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
