#pragma once

#include <glm/ext.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

class Vector2 : glm::vec2 
{
public:
	static vec2 up() { return vec2(0, 1); }
	static vec2 down() { return vec2(0, -1); }
	static vec2 left() { return vec2(-1, 0); }
	static vec2 right() { return vec2(1, 0); }
};

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

class Vector4 : glm::vec4 
{
public:
	static vec4 up() { return vec4(0, 1, 0, 0); }
	static vec4 down() { return vec4(0, -1, 0, 0); }
	static vec4 forward() { return vec4(0, 0, 1, 0); }
	static vec4 back() { return vec4(0, 0, -1, 0); }
	static vec4 left() { return vec4(-1, 0, 0, 0); }
	static vec4 right() { return vec4(1, 0, 0, 0); }
};