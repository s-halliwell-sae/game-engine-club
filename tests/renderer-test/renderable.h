#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <string>
#include "common.h"
#include "transform.h"

class RenderSystem;

class Renderable{
	friend class RenderSystem;
protected:
	std::string name;
	u32 renderPriority;
	Transform transform;

public:
	Renderable(std::string);
	virtual ~Renderable() {};

	const std::string& GetName() const;
	u32 GetRenderPriority() const;
	const Transform& GetTransform() const;
	Transform& GetTransform();

	virtual void Render(RenderSystem*) {};
};

#endif