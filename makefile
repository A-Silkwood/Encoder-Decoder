encode: encode.cpp
	g++ -std=c++11 -o encode encode.cpp

decode: decode.cpp
	g++ -std=c++11 -o decode decode.cpp

compare: compare.cpp
	g++ -std=c++11 -o compare compare.cpp
