LIBS=`pkg-config --libs sdl2` -lGL
CXXFLAGS=-std=c++11 -I/usr/local/include/spdlog/ -I/usr/local/include/glm/ -I/usr/local/include/SDL2/
BUILDDIR=../../build
.PHONY: run checkbuilddir

SRC=$(shell find . -name "*.cpp")
OBJ=$(SRC:%.cpp=%.o)

build: checkbuilddir $(BUILDDIR)/build

$(BUILDDIR)/build: $(OBJ)
	g++ $^ $(LIBS) -o$(BUILDDIR)/build

checkbuilddir:
	@if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi

run: build
	@../../build/build