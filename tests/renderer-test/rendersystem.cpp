#include "rendersystem.h"
#include <SDL.h>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

RenderSystem::RenderSystem(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	glctx = SDL_GL_CreateContext(window);
	if(!glctx) throw "GL Context failed to open";

	// Normally these are used for actually drawing things but
	//	post opengl 3.something, one needs to be bound regardless of
	//	whether or not you are using it for drawing.
	// This essentially becomes the global state
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	aspect = static_cast<float>(w)/h;
}

RenderSystem::~RenderSystem(){
	
}

float RenderSystem::GetAspect() const {
	return aspect;
}

void RenderSystem::NotifyResize(int w, int h){
	aspect = static_cast<float>(w)/h;
}