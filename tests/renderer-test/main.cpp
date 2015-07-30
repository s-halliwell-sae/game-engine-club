#include <iostream>
#include <SDL.h>

#include "rendersystem.h"
#include "renderable.h"
#include "sprite.h"

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
		rendersystem->AddRenderable(new Renderable("r1"));
		auto r2 = new Renderable("r2");
		auto r3 = new Renderable("r3");
		rendersystem->AddRenderable(r2);
		rendersystem->AddRenderable(r3, RenderPriority::Background);
		rendersystem->AddRenderable(new Renderable("r4"), RenderPriority::Foreground);
		// rendersystem->AddRenderable(new Renderable("r5"));
		// rendersystem->AddRenderable(new Renderable("r6"));
		// rendersystem->AddRenderable(new Renderable("r7"));
		// rendersystem->AddRenderable(new Renderable("r8"));
		rendersystem->Render();
		rendersystem->Render();
		rendersystem->RemoveRenderable(r2);
		rendersystem->RemoveRenderable(r3);
		rendersystem->Render();

		// Transform t{vec2(1.f, 1.f), vec2(1.f), M_PI};
		// std::cout << t << std::endl;
		// std::cout << glm::to_string(t.ComposeTransformMatrix()) << std::endl;
		// std::cout << glm::to_string(t.ComposeTransformMatrix() * vec3(1, 0.5, 1)) << std::endl;

		rendersystem->AddRenderable(new Sprite("sprite1"));
		rendersystem->Render();

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

			rendersystem->Render();

			SDL_GL_SwapWindow(window);
		}

	}catch(const char* e){
		std::cerr << "Exception!\n" << e << std::endl;
		return 1;
	}

	return 0;
}