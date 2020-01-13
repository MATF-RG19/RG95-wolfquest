CXX=g++
CC=gcc
CFLAGS=-c
LDLIBS=-lglut -lGL -lGLU

PROGRAM=wolfQuest
OBJECTS=wolfQuest.o drawFunc.o image.o
all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)

wolfQuest.o: wolfQuest.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) wolfQuest.cpp 

drawFunc.o: drawFunc.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) drawFunc.cpp

image.o: image.cpp
	$(CXX) $(CFLAGS) $(LDLIBS) image.cpp

clean:
	rm -rf *o program