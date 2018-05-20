CXXFLAGS+=-std=c++11 -Wall -O2
CXX=g++

all: ./main

run:
	./main

./main: main.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	rm -f ./main
