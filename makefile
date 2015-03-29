SOURCES = unittests.cpp 

test:
	g++ -std=c++11 $(SOURCES) -o unittests
	./unittests