CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = array.cpp slist.cpp dlist.cpp stack.cpp queue.cpp cbtree.cpp main.cpp
HDR = array.h slist.h dlist.h stack.h queue.h cbtree.h

all: dbms

dbms: $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o dbms

clean:
	rm -f dbms test.data

.PHONY: all clean
