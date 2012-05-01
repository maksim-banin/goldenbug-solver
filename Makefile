####### Compiler, tools and options

CXX           = g++
CXXFLAGS      = -pipe -O2 -Wall -Wextra
LINK          = g++

####### Files

SOURCES       = main.cpp DicExpert.cpp FreqExpert.cpp Theory.cpp 
OBJECTS       = *.o
DESTDIR       = bin

####### Compile

all:
	$(CXX) -c $(CXXFLAGS) $(SOURCES)
	mv $(OBJECTS) ./bin
	cp tests.txt ./bin
	$(LINK) ./bin/$(OBJECTS) -o ./bin/test

