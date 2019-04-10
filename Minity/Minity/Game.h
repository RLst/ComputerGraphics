//Tony Le
//21 Mar 2019

#pragma once
#include <memory>

#include "App.h"
#include "Colour.h"
#include "Shader.h"

#include "Mesh.h"
#include "OBJMesh.h"
#include "Texture.h"
#include "FlyCamera.h"
#include "Light.h"

#include "glm/ext.hpp"
#include "glm/gtc/quaternion.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

class Game : public pkr::App
{
private:

	////Camera
	struct {
		std::unique_ptr<pkr::Camera> camera;
		vec3 position = vec3(8, 4, 16);
		vec3 lookAt = vec3(0, 1, 2.5);
		float speed = 15.0f;
		//float smoothing = 0.25f;
		float fov = 25.f;
		float aspect = 16 / 9.f;
		float near = 0.1f;
		float far = 1000.f;
	} c;

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
	float m_ss_angVel;
	struct {
		//Core settings
		//const char* name;
		float radius = 1;
		vec4 colour = vec4(0.8f, 0.4f, 0, 1);

		//Transforms
		mat4 transform = mat4();
		vec3 pos = vec3(0, 0, 0);
		struct {
			float angle = 0;
			float vel = 0;
			void setAngle(float inAngle) { angle += inAngle; if (angle > 360) angle -= 360.f; else if (angle < 0) angle += 360.f; }
		} orbital;
	} m_planets[10];

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

	//Geometry
	aie::ShaderProgram								m_shaderProg;
	unique_ptr<pkr::Mesh>							m_plane;
	unique_ptr<aie::OBJMesh>						m_ferrari;
	unique_ptr<aie::OBJMesh>						m_soulspear;

	//Material

	//Lights
	const size_t									m_lightCount = 8;
	unique_ptr<pkr::AmbientLight>					m_ambientLight;
	typedef std::vector<unique_ptr<pkr::Light>>		Lights;
	Lights											m_lights;	//First light is directional (sun)

	//Direct lighting Tutorial
	aie::ShaderProgram								m_phongShader;

	//Advanced Texturing Tutorial
	unique_ptr<aie::ShaderProgram>					m_normalmapShader;

	//Multi-lights
	//unique_ptr<aie::OBJMesh>						m_ferrari;
	float											m_specularPower;
	unique_ptr<aie::ShaderProgram>					m_shader;	//Multi-light textured shader for assessment

public:
	bool Start() override;
	void Update() override;
	void Draw() override;
	bool End() override;

	void StartSolarSystem();
	void StartQuatTutorial();
	void StartRenderGeomTutorial();
	void StartLighting();
	void StartPlane();
	void StartFerrari();
	void StartSoulspear();
	void StartAssessment();
	void StartCamera();

	void UpdateQuatTutorial();
	void UpdateObjects();
	void UpdateLighting();
	void UpdateCamera();

	void DrawGridGizmo(int size);
	void DrawSolarSystem();
	void DrawQuatTutorial();
	void DrawRenderGeomTutorial();
	void DrawPlane();
	void DrawFerrari();
	void DrawSoulspear();
	void DrawAssessment();
	void DrawCamera();
};

static void BindMaterial(aie::OBJMesh* const mesh, aie::ShaderProgram* const shader, float shininess);
static void BindLights(const std::vector<unique_ptr<pkr::Light>>& lights, aie::ShaderProgram* const shader);