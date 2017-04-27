CXX = g++
CXXFLAGS = -g -c -std=c++11 -Wall -W -Werror -pedantic

rbapp: rbapp.o rbtree.o
	$(CXX) rbapp.o rbtree.o -o rbapp 
rbapp.o: rbapp.cpp rbapp.h rbtree.h
	$(CXX) $(CXXFLAGS) rbapp.cpp
rbtree.o: rbtree.cpp rbtree.h
	$(CXX) $(CXXFLAGS) rbtree.cpp
clean:
	rm -f *.o rbapp
