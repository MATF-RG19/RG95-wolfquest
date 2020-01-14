CXX=g++
CC=gcc
CFLAGS=-c
LDLIBS=-lglut -lGL -lGLU

PROGRAM=wolfQuest
OBJECTS=wolfQuest.o drawFunc.o image.o

OPTS =  -I"irrKlangLib/include" -L"/usr/lib" irrKlangLib/bin/linux-gcc-64/libIrrKlang.so -pthread

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS) $(OPTS)

wolfQuest.o: wolfQuest.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) wolfQuest.cpp 

drawFunc.o: drawFunc.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) drawFunc.cpp

image.o: image.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) image.cpp

clean:
	rm -rf *o program
