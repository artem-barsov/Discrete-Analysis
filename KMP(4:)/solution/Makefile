CXX = g++
CXXFLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OBJ = main.o search.o
OUT = solution

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp search.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

search.o: search.hpp search.cpp
	$(CXX) $(CXXFLAGS) -c search.cpp

clean:
	rm -f $(OBJ) *.txt $(OUT)
