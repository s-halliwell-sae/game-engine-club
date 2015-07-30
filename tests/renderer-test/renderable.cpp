#include "renderable.h"

using std::string;

Renderable::Renderable(string n) : name(n), transform() {}

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
