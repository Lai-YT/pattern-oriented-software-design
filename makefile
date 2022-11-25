.PHONY: dirs clean clean_coverage

CXXFLAGS = #-Wfatal-errors

# FIXME: test/**/*.h doesn't work for deep files
SRC = $(shell ls src/*.h src/*/*.h src/*/*/*.h)
TEST = $(shell ls test/*.h test/*/*.h test/*/*/*.h)
OBJ = $(shell ls src/iterator/factory/*.cpp \
	| $(STRIP_PARENT_PATH) \
	| $(REPLACE_CPP_EXTENSION_WITH_O))
# | is used as the delimiter
STRIP_PARENT_PATH = sed 's|src/iterator/factory/|obj/|g'
REPLACE_CPP_EXTENSION_WITH_O = sed 's|.cpp|.o|g'

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
coverage: clean test
	gcov test/ut_main.cpp -o bin/ut_all-ut_main $(GCOV_FLAGS)

clean_coverage:
	rm -f *.gcov **/*.gcda **/*.gcno coverage.xml coverage.html

valgrind: CXXFLAGS += -O0 -g
valgrind: clean all
	valgrind \
	--tool=memcheck --error-exitcode=1 --track-origins=yes --leak-check=full --leak-resolution=high \
	--num-callers=50 --show-leak-kinds=definite,possible --show-error-list=yes \
	bin/ut_all
