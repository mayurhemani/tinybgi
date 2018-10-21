
CCFLAGS= -std=c++11
LIBS= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
all: sierpinski

sierpinski: graphics.hpp sierpinski.cpp
	g++ $(LIBS) sierpinski.cpp -o sierpinski $(CCFLAGS) 