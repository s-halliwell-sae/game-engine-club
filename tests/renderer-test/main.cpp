#include <iostream>
#include <SDL.h>

#include "rendersystem.h"
#include "renderable.h"
#include "sprite.h"
#include "texture.h"

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

		auto sprite1 = new Sprite("sprite1");
		auto tex = new Texture();
		auto texData = new vec3[8*8];
		for(u32 y = 0; y < 8; y++)
			for(u32 x = 0; x < 8; x++){
				texData[y*8 + x] = vec3(x/8.f, y/8.f, 1.f);
			}

		tex->LoadFromMemory(texData, 8, 8, GL_RGB);
		// tex->SetFiltering(Texture::Linear);
		// tex->SetWrapping(Texture::Clamp);
		sprite1->SetTexture(tex);

		rendersystem->AddRenderable(sprite1);
		rendersystem->Render();

		SDL_Event e;
		bool running = true;
		f32 t = 0.f;

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

			t += 0.05;

			glClearColor(0.7,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);

			sprite1->GetTransform().position = vec2(cos(t*0.5)*0.7, sin(t)*0.5);
			sprite1->GetTransform().scale = vec2(sin(t*3)*0.08 + 1.f);
			sprite1->GetTransform().rotation = t*M_PI/6.f;
			rendersystem->Render();

			SDL_GL_SwapWindow(window);
		}

	}catch(const char* e){
		std::cerr << "Exception!\n" << e << std::endl;
		return 1;
	}

	return 0;
}