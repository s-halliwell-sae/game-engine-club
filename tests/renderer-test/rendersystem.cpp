#include "rendersystem.h"
#include <SDL.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include "renderable.h"

bool RenderablePriorityComparator::operator()(Renderable* a, Renderable* b) {
	// RenderPriorities closer to 0 should be rendered first so sort
	//	backwards
	return a->GetRenderPriority() < b->GetRenderPriority();
}

RenderSystem::RenderSystem(SDL_Window* window) : renderQueueDirty(false){
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
	aspect = static_cast<f32>(w)/h;

	// This is copy-pasta and gross
	// TODO: Make this go away
	std::vector<const char*> lines{"#version 330\n", nullptr}; 
	std::ifstream file("shader", std::ios::binary);
	if(!file) throw "Shader not found";

	file.seekg(0, file.end);
	auto length = file.tellg();
	file.seekg(0, file.beg);

	std::string data(length+1l, '\0');
	file.read(&data[0], length);
	lines.push_back(data.data());

	uint vsh, fsh;
	auto compileShader = [&](uint type) -> uint {
		auto sh = glCreateShader(type);

		switch(type){
			case GL_VERTEX_SHADER: lines[1] = "#define VS\n"; break;
			case GL_FRAGMENT_SHADER: lines[1] = "#define FS\n"; break;
			default: lines[1] = "";
		}

		glShaderSource(sh, lines.size(), lines.data(), nullptr);
		glCompileShader(sh);

		int status;
		glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
		if(status != GL_TRUE){
			char* buffer = new char[1024];
			glGetShaderInfoLog(sh, 1024, nullptr, buffer);

			std::cerr << buffer << std::endl;
			delete[] buffer;
			throw "Shader compile fail";
		}

		return sh;
	};

	vsh = compileShader(GL_VERTEX_SHADER);
	fsh = compileShader(GL_FRAGMENT_SHADER);

	shader = glCreateProgram();
	glAttachShader(shader, vsh);
	glAttachShader(shader, fsh);
	glLinkProgram(shader);

	glDeleteShader(vsh);
	glDeleteShader(fsh);

	int status;
	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		int logLength = 0;
		glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		char* buffer = new char[logLength];
		glGetProgramInfoLog(shader, logLength, nullptr, buffer);

		std::cerr << buffer << std::endl;
		delete[] buffer;
		throw "Program link fail";
	}

	glUseProgram(shader);
	modelMatrixLocation = glGetUniformLocation(shader, "modelMatrix");
	projViewMatrixLocation = glGetUniformLocation(shader, "projectionViewMatrix");
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

	renderQueueDirty = true;
	// std::cout << "Renderable " << r->name << " added to queue" << std::endl;
}
void RenderSystem::RemoveRenderable(Renderable* r){
	auto rit = std::find(renderQueue.begin(), renderQueue.end(), r);
	if(rit == renderQueue.end()) return;

	std::swap(*rit, *(renderQueue.end()-1));
	renderQueue.pop_back();

	renderQueueDirty = true;
	// std::cout << "Renderable " << r->name << " removed from queue" << std::endl;
}

void RenderSystem::Render(){
	if(renderQueueDirty) Sort();

	mat3 pvMatrix;
	pvMatrix[0] = vec3(1.f/aspect, 0, 0);
	pvMatrix[1] = vec3(0, 1, 0);
	pvMatrix[2] = vec3(0, 0, 1);

	glUniformMatrix3fv(projViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(pvMatrix));
	for(auto r: renderQueue){
		// std::cout << "Rendering " << r->name << std::endl;
		auto transform = r->transform.ComposeTransformMatrix();
		glUniformMatrix3fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(transform));
		r->Render(this);
	}
}

void RenderSystem::Sort(){
	std::sort(renderQueue.begin(), renderQueue.end(), RenderablePriorityComparator());
	renderQueueDirty = false;
	// std::cout << "RenderQueue sorted" << std::endl;
}