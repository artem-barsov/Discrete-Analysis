CXX = g++
CXXFLAGS = -std=c++11
OBJ = benchmark.o Record.o Sort.o
OUT = benchmark

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT)

benchmark.o: benchmark.cpp ../Vector.hpp
	$(CXX) $(CXXFLAGS) -c benchmark.cpp

Record.o: ../Record.hpp ../Record.cpp
	$(CXX) $(CXXFLAGS) -c ../Record.cpp

Sort.o: ../Sort.hpp ../Sort.cpp
	$(CXX) $(CXXFLAGS) -c ../Sort.cpp

clean:
	rm -f $(OBJ) *.txt $(OUT)
