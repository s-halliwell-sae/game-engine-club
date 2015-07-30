#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "common.h"
#include <queue>
#include <vector>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

struct SDL_Window;
class Renderable;

enum RenderPriority : u32 {
	Background,
	Default,
	Foreground,
};

struct RenderablePriorityComparator{
	bool operator()(Renderable* a, Renderable* b);
};

class RenderSystem {
public:
	using RenderQueue = std::vector<Renderable*>;

private:
	void* glctx;
	f32 aspect;

	u32 shader;
	u32 modelMatrixLocation;
	u32 projViewMatrixLocation;

	RenderQueue renderQueue;
	bool renderQueueDirty;

	void Sort();

public:
	RenderSystem(SDL_Window*);
	~RenderSystem();

	f32 GetAspect() const;
	void NotifyResize(s32 w, s32 h);

	void AddRenderable(Renderable*, u32 = RenderPriority::Default);
	void RemoveRenderable(Renderable*);
	void Render();
};

#endif