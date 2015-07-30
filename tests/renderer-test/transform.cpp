#include "transform.h"
#include <algorithm>
#include <string>

std::ostream& operator<<(std::ostream& o, const Transform& t){
	o << "Transform(";
	o << glm::to_string(t.position) << ", ";
	o << glm::to_string(t.scale) << ", ";
	o << std::to_string(t.rotation) << ")";

	return o;
}

mat3 Transform::ComposeTransformMatrix() const {
	mat3 ret;
	auto c = glm::cos(rotation) * scale;
	auto s = glm::sin(rotation) * scale;
	s.x = -s.x;

	ret[0] = vec3(c.x, s.y, 0);
	ret[1] = vec3(s.x, c.y, 0);
	ret[2] = vec3(position, 1);

	return ret;
}