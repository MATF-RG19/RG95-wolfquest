CXX	= g++
CC	= gcc
CFLAGS	= -c 
LDLIBS	= -lglut -lGL -lGLU
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
MEX	= -Ofast

PROGRAM	= wolfQuest
OBJECTS	= wolfQuest.o ./drawings/drawFunc.o ./textures/image.o ./other/handy.o

OPTS =  -I"irrKlangLib/include" -L"/usr/lib" irrKlangLib/bin/linux-gcc-64/libIrrKlang.so -pthread

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(MEH) $(OBJECTS) $(LDLIBS) $(OPTS)

wolfQuest.o: wolfQuest.cpp
	$(CXX) $(CFLAGS) $(MEH) $(LDLIBS) wolfQuest.cpp 

drawFunc.o: drawFunc.cpp
	$(CXX) $(CFLAGS) $(MEH) $(LDLIBS) ./drawings/drawFunc.cpp

image.o: image.cpp
	$(CXX) $(CFLAGS) $(MEH) $(LDLIBS) ./textures/image.cpp
handy.o: handy.cpp
	$(CXX) $(CFLAGS) $(MEH) $(LDLIBS) ./other/handy.cpp
clean:
	rm -rf *o program
