CXX = g++
CXXFLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OBJ = main.o
OUT = solution

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJ) *.txt $(OUT)
