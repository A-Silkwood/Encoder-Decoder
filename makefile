encode: encode.cpp
	g++ -std=c++11 -o encode encode.cpp

compare: utils.cpp
	g++ -std=c++11 -o compare utils.cpp
