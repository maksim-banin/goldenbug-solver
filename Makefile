####### Compiler, tools and options

CXX           = g++
CXXFLAGS      = -pipe -O2 -Wall -Wextra
LINK          = g++

####### Files

SOURCES       = *.cpp 
OBJECTS       = *.o
DESTDIR       = bin

####### Compile

all:
	$(CXX) -c $(CXXFLAGS) $(SOURCES)
	mkdir ./bin
	mv $(OBJECTS) ./bin
	cp tests.txt ./bin
	$(LINK) ./bin/$(OBJECTS) -o ./bin/test

