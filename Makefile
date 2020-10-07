

default: carrace

CPPFLAGS = -std=c++11
CXXFLAGS = -std=c99

carrace: carrace.c
	gcc -O2 -o carrace carrace.c -lpthread

clean:
	rm -rf carrace
