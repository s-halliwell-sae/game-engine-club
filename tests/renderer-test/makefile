LIBS=`pkg-config --libs sdl2` -lGL
CXXFLAGS=-std=c++11 -Wall -I/usr/local/include/spdlog/ -I/usr/local/include/glm/ -I/usr/local/include/SDL2/
BUILDDIR=../../build
.PHONY: run clean checkbuilddir

SRC=$(shell find . -name "*.cpp")
OBJ=$(SRC:%.cpp=%.o)

build: checkbuilddir $(BUILDDIR)/build

$(BUILDDIR)/build: $(OBJ)
	g++ $^ $(LIBS) -o$(BUILDDIR)/build

%.o: %.cpp %.h
	g++ $(CXXFLAGS) -c $<

checkbuilddir:
	@if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi

run: build
	@../../build/build

clean:
	rm *.o