CXX=g++
CC=gcc
CFLAGS=-c
LDLIBS=-lglut -lGL -lGLU



PROGRAM=wolfQuest
OBJECTS=wolfQuest.o drawFunc.o 
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

wolfQuest.o: wolfQuest.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) wolfQuest.cpp 

drawFunc.o: drawFunc.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) drawFunc.cpp

clean:
	rm -rf *o program
