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
//SINGLETON (LAZY. BAD)
public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
	static Game* instance()
	{
		if (!s_instance)
		{
			s_instance = new Game;
		}

		return s_instance;
	}
private:
	static Game* s_instance;
	typedef std::vector<unique_ptr<pkr::Light>> Lights;
private:

	//Input
	pkr::Input*								m_input;

	////Camera
	struct {
		std::unique_ptr<pkr::Camera> camera;
		vec3 position = vec3(10, 5, 20);
		vec3 lookAt = vec3(0, 2, 2.5);
		float speed = 30.0f;
		//float smoothing = 0.25f;
		float fov = 25.f;
		float aspect = 16 / 9.f;
		float near = 0.1f;
		float far = 1000.f;
	} c;

	//Geometry
	unique_ptr<pkr::Mesh>					m_plane;
	unique_ptr<aie::OBJMesh>				m_soulspear;
	unique_ptr<aie::OBJMesh>				m_model;

	//Lights
	std::vector<float>					   m_lightAngle;
	Lights								   m_lights;
	const size_t						   m_dirLightCount = 1;
	const size_t						   m_omniLightCount = 2;
	const size_t						   m_spotLightCount = 2;


	//Shaders
	unique_ptr<aie::ShaderProgram>		   m_planeShader;
	unique_ptr<aie::ShaderProgram>		   m_spearShader;
	unique_ptr<aie::ShaderProgram>		   m_shader;	//Multi-light textured shader for assessment

public:
	Game() = default;

	bool Start() override;
	void Update() override;
	void Draw() override;
	bool End() override;

	void SetupLighting();
	void StartPlane();
	void StartSoulspear();
	void StartAssessment();
	void StartCamera();

	void UpdateLighting();
	void UpdateCamera();

	void DrawLightingGizmos();
	void DrawGridGizmo(int size);
	void DrawPlane();
	void DrawSoulspear();
	void DrawAssessment();
	void DrawCamera();

	static void BindMaterial(aie::OBJMesh* mesh, aie::ShaderProgram* shader);
	static void BindLights(const std::vector<unique_ptr<pkr::Light>>& lights, aie::ShaderProgram* shader);
};
