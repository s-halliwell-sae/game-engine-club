#include "rendersystem.h"
#include <SDL.h>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

#include <algorithm>
#include "renderable.h"

bool RenderablePriorityComparator::operator()(Renderable* a, Renderable* b) {
	// RenderPriorities closer to 0 should be rendered first so sort
	//	backwards
	return a->renderPriority > b->renderPriority;
}

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
	u32 vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	s32 w, h;
	SDL_GetWindowSize(window, &w, &h);
	aspect = static_cast<float>(w)/h;
}

RenderSystem::~RenderSystem(){
	
}

float RenderSystem::GetAspect() const {
	return aspect;
}

void RenderSystem::NotifyResize(s32 w, s32 h){
	aspect = static_cast<float>(w)/h;
}

#include <iostream>
void RenderSystem::AddRenderable(Renderable* r, u32 priority){
	r->renderPriority = priority;
	renderQueue.push_back(r);

	std::sort(renderQueue.begin(), renderQueue.end(), RenderablePriorityComparator());
	std::cout << "Renderable " << r->name << " added to queue" << std::endl;
}

void RenderSystem::Render(){
	for(auto r: renderQueue){
		std::cout << "Rendering " << r->name << std::endl;
		r->Render(this);
	}
}