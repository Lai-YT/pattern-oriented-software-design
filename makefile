.PHONY: dirs clean clean_coverage

CXXFLAGS = -Wfatal-errors
SRC = $(shell ls src/*.h src/**/*.h)
TEST = $(shell ls test/*.h test/**/*.h)
OBJ = obj/iterator_factory.o obj/bfs_iterator_factory.o obj/dfs_iterator_factory.o obj/list_iterator_factory.o

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(OBJ) $(TEST) $(SRC)
	g++ -o $@ $< $(OBJ) -lgtest -lpthread -std=c++11 $(CXXFLAGS)

obj/%.o: src/iterator/factory/%.cpp
	g++ -o $@ -c $< -std=c++11 $(CXXFLAGS)

test: all
	bin/ut_all

dirs:
	mkdir -p bin obj

clean:
	rm -f bin/* obj/*

GCOV_FLAGS = --relative-only --branch-probabilities

coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage -O0 -fno-inline -fno-elide-constructors
coverage: test
	gcov test/ut_main.cpp -o ut_main $(GCOV_FLAGS)

clean_coverage:
	rm -f *.gcov **/*.gcda **/*.gcno coverage.xml coverage.html
