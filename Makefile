all:
	g++ -std=c++11 -o main scriptparser.cpp
	g++ -std=c++11  -o tree tree.cpp

clean:
	rm main;
	rm tree;                                       
