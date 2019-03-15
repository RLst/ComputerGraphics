#pragma once
#include "App.h"

#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

class Game : public pkr::App
{
private:
	struct {
		vec4 lightGrey = vec4(0.1f, 0.1f, 0.1f, 1);
		vec4 white = vec4(1);
		vec4 black = vec4(0, 0, 0, 1);
		vec4 sun = vec4(1, 0.60f, 0, 1);
	} m_colours;

	mat4 m_view;
	mat4 m_projection;

	//Solar system
	struct {
		float sun = 1.f / 24;
		float mercury = 47.87f;
		float venus = 35.02f;
		float earth = 29.78f;
		float mars = 24.077f;
		float jupiter = 13.07f;
		float saturn = 9.69f;
		float uranus = 6.81f;
		float neptune = 5.43f;
	} speed;

	float m_ss_angle;
	struct {
		//const char* name;
		float radius = 1;
		vec4 colour = vec4(0.8f, 0.4f, 0, 1);

		vec3 pos = vec3(0,0,0);
		struct {
			float angle = 0;
			float vel = 0;
		} orbital;
	} m_planets[10];

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

