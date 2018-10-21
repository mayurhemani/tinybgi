
CCFLAGS= -std=c++11
LIBS= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
all: sierpinski mandelbrot julia

sierpinski: graphics.hpp sierpinski.cpp
	g++ $(LIBS) sierpinski.cpp -o sierpinski $(CCFLAGS) 

mandelbrot: graphics.hpp mandelbrot.cpp
	g++ $(LIBS) mandelbrot.cpp -o mandelbrot $(CCFLAGS) 

julia: graphics.hpp julia.cpp
	g++ $(LIBS) julia.cpp -o julia $(CCFLAGS) 