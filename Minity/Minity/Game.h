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

//namespace pkr {
//	class Camera;
//	//class Mesh;
//}
//namespace aie {
//	class OBJMesh;
//	class Texture;
//}

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;
using std::unique_ptr;

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

	////Rendering geometry
	aie::ShaderProgram					m_shaderProg;

	mat4								m_planeTransform;
	aie::Texture						m_planeTexture;
	unique_ptr<pkr::Mesh>				m_planeMesh;
	//aie::OBJMesh						m_demoObj;
	unique_ptr<aie::OBJMesh>			m_demoObj;
	mat4								m_demoTransform;

	//Direct lighting
	aie::ShaderProgram					m_phongShader;
	pkr::Light							m_light;
	glm::vec3							m_ambientLight;
	float								m_specularPower = 0.01f;
	   
public:
	bool Start() override;
	void Update() override;
	void Draw() override;
	bool End() override;

	void StartSolarSystem();
	void StartQuatTutorial();
	void StartRenderGeomTutorial();
	void StartMaterialAndTextures();
	void StartLighting();

	void UpdateQuatTutorial();
	void UpdateLighting();
	void UpdateCamera();

	void DrawGridGizmo(int size);
	void DrawSolarSystem();
	void DrawQuatTutorial();
	void DrawRenderGeomTutorial();
	void DrawLighting();
};

