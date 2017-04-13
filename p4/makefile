CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic

minpriority: main.o minpriority.o
	$(CXX) main.o minpriority.o -o minpriority

main.o: main.cpp minpriority.h
	$(CXX) $(CXXFLAGS) main.cpp

minpriority.o: minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp

clean:
	rm *.o minpriority
