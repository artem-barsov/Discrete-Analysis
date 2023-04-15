CXX = g++
CXXFLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OBJ = main.o suffix_tree.o
OUT = solution

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp suffix_tree.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

suffix_tree.o: suffix_tree.hpp suffix_tree.cpp
	$(CXX) $(CXXFLAGS) -c suffix_tree.cpp

clean:
	rm -f $(OBJ) *.txt $(OUT)
