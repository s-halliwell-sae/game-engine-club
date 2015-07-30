#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "common.h"

struct Transform {
	vec2 position;
	vec2 scale;
	f32 rotation;

	mat3 ComposeTransformMatrix() const;
};

#include <ostream>
std::ostream& operator<<(std::ostream& o, const Transform& t);

#endif