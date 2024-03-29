.PHONY: dirs clean clean_coverage

CXXFLAGS = -std=c++17 -Wfatal-errors -g -O0 -fno-elide-constructors # let's do things careful

SRC = $(shell find src/ -name *.h)
TEST = $(shell find test/ -name *.h)
OBJ = $(shell ls src/iterator/factory/*.cpp \
	| $(STRIP_PARENT_PATH) \
	| $(REPLACE_CPP_EXTENSION_WITH_O))
# | is used as the delimiter
STRIP_PARENT_PATH = sed 's|src/iterator/factory/|obj/|g'
REPLACE_CPP_EXTENSION_WITH_O = sed 's|.cpp|.o|g'

all: dirs bin/ut_all

bin/ut_all: test/ut_main.cpp $(OBJ) $(TEST) $(SRC)
	g++ -o $@ $< $(OBJ) -lgtest -pthread $(CXXFLAGS)

obj/%.o: src/iterator/factory/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

test: all
	bin/ut_all

dirs:
	mkdir -p bin obj

clean:
	rm -f bin/* obj/*

GCOV_FLAGS = --relative-only --branch-probabilities

# FIXME: files under src/iterator/factory aren't detected
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
