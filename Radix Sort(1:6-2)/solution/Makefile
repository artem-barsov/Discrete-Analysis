CXX = g++
CXXFLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OBJ = main.o Record.o Sort.o
OUT = solution

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp Vector.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Record.o: Record.hpp Record.cpp
	$(CXX) $(CXXFLAGS) -c Record.cpp

Sort.o: Sort.hpp Sort.cpp
	$(CXX) $(CXXFLAGS) -c Sort.cpp

clean:
	rm -f $(OBJ) *.txt $(OUT)
