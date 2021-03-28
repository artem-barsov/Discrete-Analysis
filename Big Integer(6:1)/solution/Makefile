CXX = g++
CXXFLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OBJ = main.o BigInteger.o
OUT = solution

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp BigInteger.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

BigInteger.o: BigInteger.hpp BigInteger.cpp
	$(CXX) $(CXXFLAGS) -c BigInteger.cpp

clean:
	rm -f $(OBJ) *.txt $(OUT)
