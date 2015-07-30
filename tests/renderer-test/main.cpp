#include <iostream>
#include <SDL.h>

#ifdef WIN32
#undef main
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

// TODO: Test to see if glew requires Windows.h like gl.h on windows does
#include <GL/glew.h>
#include "rendersystem.h"

int main(){
	try{
		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			throw "SDL Init failed";
		}

		auto window = SDL_CreateWindow("Renderer test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

		if(!window){
			throw "SDL_CreateWindow failed";
		}

		auto rendersystem = new RenderSystem(window);

		SDL_Event e;
		bool running = true;

		while(running){
			while(SDL_PollEvent(&e)){
				switch(e.type){
					case SDL_QUIT: running = false; break;
					case SDL_KEYDOWN:
						if(e.key.keysym.sym == SDLK_ESCAPE)
							running = false;
						
						break;
					
					case SDL_WINDOWEVENT:
						if(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
							rendersystem->NotifyResize(e.window.data1, e.window.data2);

						break;
				}
			}

			glClearColor(0.7,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);

			SDL_GL_SwapWindow(window);
		}

	}catch(const char* e){
		std::cerr << "Exception!\n" << e << std::endl;
		return 1;
	}

	return 0;
}