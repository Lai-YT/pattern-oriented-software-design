.PHONY: dirs clean clean_coverage

CXXFLAGS = -Wfatal-errors
SRC = $(shell ls src/*.h)
TEST = $(shell ls test/*.h)

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(TEST) $(SRC)
	g++ -std=c++11 $< -o $@ -lgtest -pthread $(CXXFLAGS)

test: all
	bin/ut_all

dirs:
	mkdir -p bin

clean:
	rm -f bin/*

GCOV_FLAGS = --relative-only --branch-probabilities

coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage -O0 -fno-inline -fno-elide-constructors
coverage: test
	gcov test/ut_main.cpp -o bin/ut_all-ut_main $(GCOV_FLAGS)

clean_coverage:
	rm -f *.gcov **/*.gcda **/*.gcno coverage.xml coverage.html
