#pragma once

#include <glm/ext.hpp>

using glm::vec3;

class Vector3 : glm::vec3
{
public:
	static vec3 up() { return vec3(0, 1, 0); }
	static vec3 down() { return vec3(0, -1, 0); }
	static vec3 forward() { return vec3(0, 0, 1); }
	static vec3 back() { return vec3(0, 0, -1); }
	static vec3 left() { return vec3(-1, 0, 0); }
	static vec3 right() { return vec3(1, 0, 0); }

};

