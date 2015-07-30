#include <iostream>
#include <SDL.h>
#undef main

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <GL/gl.h>

int main(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cerr << "SDL Init failed" << std::endl;
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	auto window = SDL_CreateWindow("Renderer test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL);

	if(!window){
		std::cerr << "SDL_CreateWindow failed" << std::endl;
		return -1;
	}

	auto glctx = SDL_GL_CreateContext(window);

	if(!glctx){
		std::cerr << "GL Context failed to open" << std::endl;
		return -1;
	}

	SDL_Event e;
	bool running = true;

	while(running){
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT: running = false; break;
				case SDL_KEYDOWN:{
					if(e.key.keysym.sym == SDLK_ESCAPE){
						running = false;
					}
					break;
				}
			}
		}

		glClearColor(0.7,0,1,1);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window);
	}


	return 0;
}