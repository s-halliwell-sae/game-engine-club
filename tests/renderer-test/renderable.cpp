#include "renderable.h"

using std::string;

Renderable::Renderable(string n) : name(n), transform{vec2(0,0), vec2(1,1), 0} {
	
}

const string& Renderable::GetName() const {
	return name;
}

u32 Renderable::GetRenderPriority() const {
	return renderPriority;
}

const Transform& Renderable::GetTransform() const {
	return transform;
}
Transform& Renderable::GetTransform() {
	return transform;
}
