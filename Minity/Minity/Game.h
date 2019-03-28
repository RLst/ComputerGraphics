//Tony Le
//21 Mar 2019

#pragma once
#include <memory>

#include "App.h"
#include "Colour.h"
#include "Shader.h"

#include "glm/ext.hpp"
#include "glm/gtc/quaternion.hpp"

namespace pkr {
	class Camera;
}
namespace tut {
	class Mesh;
}

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

class Game : public pkr::App
{
private:

	////Camera
	struct {
		std::unique_ptr<pkr::Camera> camera;
		vec3 position = vec3(0, 10, -10);
		vec3 lookAt = vec3(0, 0, 0);
		float fov = 50.f;
		float aspect = 16 / 9.f;
		float near = 0.1f;
		float far = 1000.f;
	} m_cam;

	////Solar system
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

	////Quaternions tutorial
	//Flying box
	vec3 m_positions[3];
	quat m_rotations[3];
	struct {
		vec3 p;
		quat r;
		mat4 m;
	} box;
	
	//Leg
	struct KeyFrame {
		glm::vec3 position;
		glm::quat rotation;
	};
	KeyFrame m_hipFrames[2];
	KeyFrame m_kneeFrames[2];
	KeyFrame m_ankleFrames[2];
	glm::mat4 m_hipBone;
	glm::mat4 m_kneeBone; 
	glm::mat4 m_ankleBone;
	vec3 m_hipPos;
	vec3 m_kneePos;
	vec3 m_anklePos;

	////Rendering geometry
	aie::ShaderProgram m_shader;
	std::unique_ptr<tut::Mesh> m_quadMesh;
	mat4 m_quadTransform;
	   
	float m_ss_angVel;
	struct {
		//Core settings
		//const char* name;
		float radius = 1;
		vec4 colour = vec4(0.8f, 0.4f, 0, 1);

		//Transforms
		mat4 transform = mat4();
		vec3 pos = vec3(0,0,0);
		struct {
			float angle = 0;
			float vel = 0;
			void setAngle(float inAngle) { angle += inAngle; if (angle > 360) angle -= 360.f; else if (angle < 0) angle += 360.f; }
		} orbital;
	} m_planets[10];

public:
	Game();
	~Game();

	bool Start() override;
	void Update() override;
	void Draw() override;
	bool End() override;

	void StartSolarSystem();
	void StartQuatTutorial();
	void StartRenderGeomTutorial();
	void UpdateQuatTutorial();
	void DrawGrid(int size);
	void DrawSolarSystem();
	void DrawQuatTutorial();
	void DrawRenderGeomTutorial();
};

