CXX = g++
CXXFLAGS = -std=c++20
# CXXFLAGS = -pedantic -Wall -std=c++11 -Werror -Wno-sign-compare -O2 -lm
OBJ = main.o Data.o NBC.o
OUT = NBC

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp Data.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Data.o: Data.hpp Data.cpp
	$(CXX) $(CXXFLAGS) -c Data.cpp

NBC.o: NBC.hpp NBC.cpp
	$(CXX) $(CXXFLAGS) -c NBC.cpp

clean:
	rm -f $(OBJ) $(OUT)
