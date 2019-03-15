#pragma once
#include "App.h"

#include <glm/ext.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Game : public pkr::App
{
private:
	mat4 m_view;
	mat4 m_projection;

	struct {
		vec4 lightGrey = vec4(0.1f, 0.1f, 0.1f, 1);
		vec4 white = vec4(1);
		vec4 black = vec4(0, 0, 0, 1);
		vec4 sun = vec4(1, 0.60f, 0, 1);
	} m_colours;

public:
	Game();
	~Game();

	bool Awake() override;
	bool Start() override;
	void Update() override;
	void Draw() override;
	bool End() override;

	void clearScreen(const vec4 & backgroundColour);
	void drawGrid();
};

