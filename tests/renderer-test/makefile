LIBS=-ljemalloc -pthread -llua5.1 `pkg-config --libs sdl2` -lGL
CXXFLAGS=-std=c++11 -I/usr/local/include/spdlog/ -I/usr/local/include/glm/ -I/usr/local/include/SDL2/ -I/usr/include/lua5.1/ -I/usr/include/GL/
BUILDDIR=../../build
.PHONY: run checkbuilddir

OBJ=main.o

build: checkbuilddir $(BUILDDIR)/build

$(BUILDDIR)/build: $(OBJ)
	g++ $^ $(LIBS) -o$(BUILDDIR)/build

checkbuilddir:
	@if [ ! -d $(BUILDDIR) ]; then mkdir $(BUILDDIR); fi

run: build
	@../../build/build