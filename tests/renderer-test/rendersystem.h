#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "common.h"
#include <queue>
#include <vector>

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
	float aspect;

	RenderQueue renderQueue;
	bool renderQueueDirty;

	void Sort();

public:
	RenderSystem(SDL_Window*);
	~RenderSystem();

	float GetAspect() const;
	void NotifyResize(s32 w, s32 h);

	void AddRenderable(Renderable*, u32 = RenderPriority::Default);
	void RemoveRenderable(Renderable*);
	void Render();
};

#endif