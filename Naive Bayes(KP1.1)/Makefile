CXX = g++
CXXFLAGS = -std=c++17
OBJ = main.o Data.o NBC.o
OUT = NBC

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

main.o: main.cpp Data.hpp NBC.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Data.o: Data.hpp Data.cpp
	$(CXX) $(CXXFLAGS) -c Data.cpp

NBC.o: NBC.hpp NBC.cpp
	$(CXX) $(CXXFLAGS) -c NBC.cpp

clean:
	rm -f $(OBJ) $(OUT)
