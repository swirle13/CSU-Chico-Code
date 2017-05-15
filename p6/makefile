CXX = g++
CXXFLAGS = -g -c -std=c++11 -Wall -W -Werror -pedantic

mstapp: mstapp.o graph.o minpriority.o
	$(CXX) mstapp.o graph.o minpriority.o -o mstapp
mstapp.o: mstapp.cpp mstapp.h
	$(CXX) $(CXXFLAGS) mstapp.cpp
graph.o: graph.cpp graph.h
	$(CXX) $(CXXFLAGS) graph.cpp
minpriority.o: minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp
clean:
	rm -f *.o mstapp
