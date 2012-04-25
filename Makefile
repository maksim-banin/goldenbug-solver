####### Compiler, tools and options

CXX           = g++
CXXFLAGS      = -pipe -O2 -Wall -Wextra
LINK          = g++

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = *.cpp 
OBJECTS       = *.o
DESTDIR       = bin

####### Compile

all:
	$(CXX) -c $(CXXFLAGS) $(SOURCES)
	mv $(OBJECTS) ./bin
	$(LINK) ./bin/$(OBJECTS) -o ./bin/test
	./bin/test

