all:
	g++ -std=c++11 -o main scriptparser.cpp
	g++ -std=c++11  -o tree tree.cpp

debug:
        g++ -std=c++11 -g -O0 -o tree tree.cpp                                         
