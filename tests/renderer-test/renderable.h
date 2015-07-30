#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "common.h"
#include <string>

class RenderSystem;

class Renderable{
	friend struct RenderablePriorityComparator;
	friend class RenderSystem;
private:
	std::string name;
	u32 renderPriority;

public:
	Renderable(std::string);
	virtual ~Renderable() {};

	virtual void Render(RenderSystem*) {};
};

#endif