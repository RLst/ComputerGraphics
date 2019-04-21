//Tony Le
//21 Mar 2019

#include "Game.h"

#include <iostream>
#include <string>

#include "Gizmos.h"
#include "FlyCamera.h"
#include "Vector.h"
#include "Mesh.h"
#include "Input.h"
#include "OBJMesh.h"
#include "Random.h"
#include "imgui.h"

#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"
#include "GLFW/glfw3.h"

using namespace pkr;

Game* Game::s_instance = nullptr;

/////////// MAIN LOOP //////////////
bool Game::Start()
{
	//Init Input manager
	m_input = Input::getInstance();

	StartLighting();
	StartPlane();
	StartSoulspear();		//Advanced Texturing Tutorials
	StartAssessment();
	StartCamera();
	return true;
}

void Game::Update()
{
	UpdateLighting();
	UpdateCamera();
}

void Game::Draw()
{
	DrawGridGizmo(50);
	DrawLightingGizmos();
	DrawPlane();
	DrawSoulspear();
	DrawAssessment();
	DrawCamera();
}

bool Game::End()
{
	return true;
}
//////////////////////////////////////////////


//STARTS
void Game::StartLighting()
{
	//Good light settings: diffuse = 0.95, specular = 0.12-0.2, specularPower = 0.00000001 (this should have a range between 0-128. Check shader code)
	////WET CAR LOOK
	//m_ambientLight->diffuse = glm::vec3(0.2f); m_lights[0]->diffuse = glm::vec3(0.6f); m_lights[0]->specular = glm::vec3(0.21f); m_specularPower = 0.0001f;

	float Ca = 0.2f;
	float Cd = 0.6f;
	float Cs = 0.5f;
	float SP = 0.00001f;

	//---- Sun ----
	for (int i = 0; i < m_dirLightCount; ++i)
	{
		m_lights.push_back(make_unique<DirectionalLight>());
		//vec3 randomDir = glm::normalize(vec3(Random::range(-1, 1), Random::range(-1, 1), Random::range(-1, 1)));
		m_lights.back()->direction = vec3(0.5, -0.5, -0.5);
		m_lights.back()->position = vec3(-7.5f, 7.5f, 7.5f);
		m_lights.back()->ambient = vec3(Ca);
		m_lights.back()->diffuse = vec3(Cd);
		m_lights.back()->specular = vec3(Cs);
	}

	//---- Omni Lights ----
	for (int i = 0; i < m_omniLightCount; ++i)
	{
		static float orbRad = 5.f;
		static float constant = 1.0f;
		static float minlinear = 0.001f, maxlinear = 0.5f;
		static float quadFactor = 1.5f;

		//type
		m_lights.push_back(make_unique<OmniLight>());

		//position
		vec3 randPos(glm::normalize(vec3(Random::range(-orbRad, orbRad), Random::range(0.f, orbRad), Random::range(-orbRad, orbRad))));
		m_lights.back()->position = glm::normalize(randPos) * orbRad;

		//direction (point lights don't have direction)
		m_lights.back()->direction = vec3(0);

		//Ia, ambient
		m_lights.back()->ambient = vec3(Ca);

		//Id, diffuse
		m_lights.back()->diffuse = Colour::random();

		//Is, specular
		m_lights.back()->specular = vec3(Cs);

		//constant (always 1.0f)
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->constant = constant;

		//linear
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->linear = Random::range(minlinear, maxlinear);

		//quadratic
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->quadratic = Random::range(minlinear * quadFactor, maxlinear * quadFactor);
	}

	//---- Spot lights ----
	for (int i = 0; i < m_spotLightCount; ++i)
	{
		static float orbRad = 7.f;
		static float constant = 1.0f;
		static float minlinear = 0.01f, maxlinear = 0.05f;
		static float quadfactor = 1.5f;
		static float mincutoff = 0, maxcutoff = glm::pi<float>();
		//static float minoutcutoff = 0, maxoutcutoff = glm::pi<float>();

		//type
		m_lights.push_back(make_unique<SpotLight>());

		//position
		vec3 randPos(glm::normalize(vec3(Random::range(-orbRad, orbRad), Random::range(0.f, orbRad), Random::range(-orbRad, orbRad))));
		m_lights.back()->position = glm::normalize(randPos) * orbRad;

		//direction
		vec3 randDir(glm::normalize(vec3(Random::range(-orbRad, orbRad), Random::range(-orbRad, 0.f), Random::range(-orbRad, orbRad))));
		m_lights.back()->direction = glm::normalize(randDir);

		//Ia, ambient
		m_lights.back()->ambient = vec3(Ca);

		//Id, diffuse
		m_lights.back()->diffuse = Colour::random();

		//Is, specular
		m_lights.back()->specular = vec3(Cs);

		//constant (always 1.0f)
		dynamic_cast<pkr::SpotLight*>(m_lights.back().get())->constant = constant;

		//linear
		dynamic_cast<pkr::SpotLight*>(m_lights.back().get())->linear = Random::range(minlinear, maxlinear);

		//quadratic
		dynamic_cast<pkr::SpotLight*>(m_lights.back().get())->quadratic = Random::range(minlinear * quadfactor, maxlinear * quadfactor);

		//cutoff
		float randcutoff = Random::range(mincutoff, maxcutoff);
		dynamic_cast<pkr::SpotLight*>(m_lights.back().get())->cutOff = randcutoff;

		//outcutoff
		dynamic_cast<pkr::SpotLight*>(m_lights.back().get())->outerCutOff = randcutoff;
	}
}
void Game::StartPlane()
{
	//Setup shader
	m_planeShader = make_unique<aie::ShaderProgram>();
	m_planeShader->loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_planeShader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if (m_planeShader->link() == false)
	{
		printf("Shader Linking Error: %s\n", m_planeShader->getLastError());
		assert(false);
	}

	//Plane
	m_plane = std::make_unique<pkr::Mesh>();
	if (m_plane->texture.load("./assets/Texture/numbered_grid.tga") == false)
	{
		printf("Failed to load texture!\n");
		assert(false);
	}
	m_plane->transform = glm::scale(vec3(50));
	m_plane->initialiseQuad();
}
void Game::StartSoulspear()
{
	//Load normal map texture
	m_spearShader = std::make_unique<aie::ShaderProgram>(); //Allocate
	m_spearShader->loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_spearShader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if (m_spearShader->link() == false) {
		printf("Error linking shader: %s\n", m_spearShader->getLastError());
		assert(false);
	}

	//Setup
	m_soulspear = std::make_unique<aie::OBJMesh>();	//Allocate
	m_soulspear->material.specularPower = 1;
	m_soulspear->transform = glm::translate(vec3(10, 0, -10));

	//Load soulspear
	if (m_soulspear->load("./assets/soulspear.obj", true, true) == false) {	//This object needs 
		printf("Error loading mesh!\n");
		assert(false);
	}

	//Load textures
	if (m_soulspear->material.diffuseTexture.load("./assets/Texture/soulspear_diffuse.tga") == false) {
		printf("Error loading diffuse texture!\n");
		assert(false);
	}
	if (m_soulspear->material.normalTexture.load("./assets/Texture/soulspear_normal.tga") == false) {
		printf("Error loading normal texture!\n");
		assert(false);
	}
	if (m_soulspear->material.specularTexture.load("./assets/Texture/soulspear_specular.tga") == false) {
		printf("Error loading specular texture!\n");
		assert(false);
	}
}
void Game::StartAssessment()
{
	//Init shader program
	m_shader = make_unique<aie::ShaderProgram>();
	m_shader->loadShader(aie::eShaderStage::VERTEX, "./shaders/comprehensive.vert");
	m_shader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/multilights.frag");
	if (m_shader->link() == false) {
		printf("Error linking shader: %s\n", m_shader->getLastError());
		assert(false);
	}

	////Setup mesh
	m_model = make_unique<aie::OBJMesh>();
	m_model->transform = mat4(1) * glm::translate(vec3(0, 0, 0)) * glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));

	//Load mesh
	if (m_model->load("./assets/LaFerrari.obj") == false) {
		printf("Error loading mesh!\n");
		assert(false);
	}

	//Load textures
	//if (m_model->material.diffuseTexture.load("./assets/Texture/numbered_grid.tga") == false) {
	//	printf("Error loading diffuse texture!\n");
	//	assert(false);
	//}
	//if (m_model->material.specularTexture.load("./assets/Texture/soulspear_specular.tga") == false) {
	//	printf("Error loading specular texture!\n");
	//	assert(false);
	//}
	//if (m_model->material.normalTexture.load("./assets/Texture/soulspear_normal.tga") == false) {
	//	printf("Error loading normal texture!\n");
	//	assert(false);
	//}
}
void Game::StartCamera()
{
	c.camera = make_unique<FlyCamera>(c.position, c.lookAt, c.speed, c.fov, c.aspect, c.near, c.far);
}

//UPDATES
void Game::UpdateLighting()
{
	Input* input = Input::getInstance();

	//query time since application started
	float t = (float)Time::time() * 0.5f;

	static int selectedLight = 1;	//-1 = No light selected
	static int adjustMode = 0;	//0 = position, 1 = direction
	static float adjustSpeedFactor = 0.008f;
	static float positionRange = 20.0f;
	static bool simplifiedColors = true;

	ImGui::Begin("Computer Graphics");
	{
		ImGui::TextColored(ImVec4(1, 0.5, 0, 1), "Adjust light position and direction");
		ImGui::TextWrapped("Select adjust mode; Select a light to modify (click on light label); [Left Click] + [Move Mouse] Adjust XZ axes; [Left Click] + [Shift] Adjust Y axis");
		ImGui::TextColored(ImVec4(1, 0.5, 0, 1), "Camera controls");
		ImGui::TextWrapped("[Right Click] OR [Space] + [Move Mouse] Free Look; [WASD] Fly; [QE] Fly Up/Down; [Shift] Faster; [Ctrl] Slower");
		ImGui::Separator();
		ImGui::Text("Adjust Mode: "); ImGui::SameLine();
		ImGui::RadioButton("None", &adjustMode, -1); ImGui::SameLine();
		ImGui::RadioButton("Position", &adjustMode, 0); ImGui::SameLine(); 
		ImGui::RadioButton("Direction", &adjustMode, 1);
		ImGui::Checkbox("Simplified Colors", &simplifiedColors);
		ImGui::Separator();

		//Loop through all lights
		for (int i = 0; i < m_lights.size(); ++i)
		{
			ImGui::PushID(i);	//Required otherwise each imgui control will be linked together

			//Display light number and type of light
			char label[32];
			sprintf_s(label, "Light %d", i);
			if (ImGui::Selectable(label, selectedLight == i)) selectedLight = i;
			ImGui::SameLine();
			switch (m_lights[i]->type)
			{
			case LightType::DIRECTIONAL: ImGui::Text("Directional"); break;
			case LightType::OMNI: ImGui::Text("Omni"); break;
			case LightType::SPOT: ImGui::Text("Spot"); break;
			}

			//--------- Edit light positions and direction ---------------
			if (i == selectedLight)
			{
				//ImGui::GetIO().WantCaptureMouse = true;
				//if (!ImGui::IsMouseHoveringAnyWindow())	//This will be false if you drag a widget
				//{
					if (input->isMouseButtonDown(pkr::Mouse0) && !ImGui::IsMouseHoveringAnyWindow())
					{
						//Disable cursor
						glfwSetInputMode(getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

						float xInput = 0, yInput = 0, zInput = 0;
						if (input->isKeyDown(pkr::LeftShift))
						{
							yInput = input->getMouseDeltaY() * adjustSpeedFactor;
						}
						else
						{
							xInput = input->getMouseDeltaX() * adjustSpeedFactor;
							zInput = input->getMouseDeltaY() * adjustSpeedFactor;
						}

						if (adjustMode == 0)	//Position
						{
							m_lights[selectedLight]->position.x += xInput * glm::cos(c.camera->getRotation().y) + zInput * glm::sin(c.camera->getRotation().y);
							m_lights[selectedLight]->position.y += yInput;
							m_lights[selectedLight]->position.z -= zInput * glm::cos(c.camera->getRotation().y) - xInput * glm::sin(c.camera->getRotation().y);
						}
						else if (adjustMode == 1)	//Direction
						{
							m_lights[selectedLight]->direction.x += xInput;
							m_lights[selectedLight]->direction.y += yInput;
							m_lights[selectedLight]->direction.z -= zInput;
							m_lights[selectedLight]->direction = glm::normalize(m_lights[selectedLight]->direction);
						}
					}
					else if (input->isMouseButtonUp(pkr::Mouse0))
					{
						//Re-enable cursor
						glfwSetInputMode(getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					}
				//}
			}

			//----------- Display light modifiables ----------------
			//Position
			ImGui::SliderFloat3("Position", glm::value_ptr(m_lights[i]->position), -positionRange, positionRange);
			//Direction
			if (m_lights[i]->type != LightType::OMNI)
				ImGui::SliderFloat3("Direction", glm::value_ptr(m_lights[i]->direction), -1.0f, 1.0f);
			if (simplifiedColors)
			{
				if (ImGui::ColorEdit3("Color", glm::value_ptr(m_lights[i]->ambient))) { //Simplified, combined all colors into one
					m_lights[i]->diffuse = m_lights[i]->ambient;
					m_lights[i]->specular = m_lights[i]->ambient;
				}
			}
			else
			{
				ImGui::ColorEdit3("Ambient", glm::value_ptr(m_lights[i]->ambient));
				ImGui::ColorEdit3("Diffuse", glm::value_ptr(m_lights[i]->diffuse));
				ImGui::ColorEdit3("Specular", glm::value_ptr(m_lights[i]->specular));
			}
			if (m_lights[i]->type == LightType::OMNI || m_lights[i]->type == LightType::SPOT)
			{
				ImGui::Text("Constant: %f", dynamic_cast<OmniLight*>(m_lights[i].get())->constant);
				ImGui::SliderFloat("Linear", &dynamic_cast<OmniLight*>(m_lights[i].get())->linear, 0.000001f, 0.5f);
				ImGui::SliderFloat("Quadratic", &dynamic_cast<OmniLight*>(m_lights[i].get())->quadratic, 0.001f, 3.f);
			}
			if (m_lights[i]->type == LightType::SPOT)
			{
				ImGui::SliderFloat("Cut Off", &dynamic_cast<SpotLight*>(m_lights[i].get())->cutOff, 0, 30);
				ImGui::SliderFloat("Outer Cut Off", &dynamic_cast<SpotLight*>(m_lights[i].get())->outerCutOff, 0, 30);
			}

			ImGui::Separator();

			ImGui::PopID();
		}
	}
	ImGui::End();
}
void Game::UpdateCamera()
{
	//ImGui::Begin("Camera Debug");
	//ImGui::Text("Camera UP: %f, %f, %f", c.camera->up().x, c.camera->up().y, c.camera->up().z);
	//vec3 cang = c.camera->getRotation();
	//ImGui::Text("camera.getRotation(): %f, %f, %f", cang.x, cang.y, cang.z);
	//ImGui::End();
	c.camera->update();
}

//DRAWS
void Game::DrawGridGizmo(int size)
{
	aie::Gizmos::addTransform(mat4(1), 15.f);	//Draw the little tri coloured gizmo at the centre

	if (size % 2 == 1) --size;	//round to the nearest even number
	if (size == 0) size = 2;	//protect from divide by zero
	int halfsize = size / 2;

	//Draw grid
	for (int i = 0; i <= size; ++i)
	{
		aie::Gizmos::addLine(vec3(-halfsize + i, 0, halfsize), vec3(-halfsize + i, 0, -halfsize), i == halfsize ? pkr::Colour::shade(0.85f) : pkr::Colour::shade(0.15f));
		aie::Gizmos::addLine(vec3(halfsize, 0, -halfsize + i), vec3(-halfsize, 0, -halfsize + i), i == halfsize ? pkr::Colour::shade(0.85f) : pkr::Colour::shade(0.15f));
	}
}
void Game::DrawPlane()
{
	//Shader Bindings
	m_planeShader->bind();
	m_planeShader->bindUniform("ProjectionViewModel", c.camera->getProjectionView() * m_plane->transform);

	static float intensity = 0.6f;
	m_planeShader->bindUniform("Intensity", intensity);
	m_planeShader->bindUniform("DiffuseTexture", 0);
	m_plane->texture.bind(0);
	//Draw plane
	m_plane->draw();
}
void Game::DrawLightingGizmos()
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->DrawVisualisation();
	}
}
void Game::DrawSoulspear()
{
	////Shader Bindings (all in order of binding)
	m_spearShader->bind();

	m_spearShader->bindUniform("ProjectionViewModel", c.camera->getProjectionView() * m_soulspear->transform);

	static float intensity = 0.75f;
	m_spearShader->bindUniform("Intensity", intensity);
	m_spearShader->bindUniform("DiffuseTexture", 0);
	m_soulspear->material.diffuseTexture.bind(0);

	//Vertex
	//m_spearShader->bindUniform("uProjectionViewModel", c.camera->getProjectionView() * m_soulspear->transform);
	//m_spearShader->bindUniform("uModel", m_soulspear->transform);
	//m_spearShader->bindUniform("uNormal", glm::inverseTranspose(glm::mat3(m_soulspear->transform)));

	//Fragment
	//m_soulspear->material.diffuseTexture.bind(0);
	//m_soulspear->material.normalTexture.bind(1);
	//m_soulspear->material.specularTexture.bind(2);
	//m_spearShader->bindUniform("diffuseTexture", 0);
	//m_spearShader->bindUniform("normalTexture", 1);
	//m_spearShader->bindUniform("specularTexture", 2);

	//m_spearShader->bindUniform("ViewPos", c.camera->getPosition());

	////m_spearShader->bindUniform("Ka", vec3(0.2f));
	////m_spearShader->bindUniform("Kd", vec3(0.6f));
	////m_spearShader->bindUniform("Ks", vec3(0.2f));
	//m_spearShader->bindUniform("specularPower", m_soulspear->material.specularPower);

	//m_spearShader->bindUniform("Ia", m_lights[0]->ambient);
	//m_spearShader->bindUniform("Id", m_lights[0]->diffuse);
	//m_spearShader->bindUniform("Is", m_lights[0]->specular);
	//m_spearShader->bindUniform("LightDirection", m_lights[0]->direction);

	//Draw
	m_soulspear->draw();
}
void Game::DrawAssessment()
{
	////Shader bindings
	m_shader->bind();
	///Vertex
	m_shader->bindUniform("uModel", m_model->transform);
	m_shader->bindUniform("uView", c.camera->getView());
	m_shader->bindUniform("uProjection", c.camera->getProjection());
	///Fragment
	m_shader->bindUniform("ViewPos", c.camera->getPosition());

	//Material
	//BindMaterial(m_model.get(), m_shader.get());

	//Lights
	BindLights(m_lights, m_shader.get());

	m_model->draw();
}
void Game::BindMaterial(aie::OBJMesh* mesh, aie::ShaderProgram* shader)
{
	mesh->material.diffuseTexture.bind(0);
	mesh->material.normalTexture.bind(1);
	mesh->material.specularTexture.bind(2);

	shader->bindUniform("material.diffuse", 0);
	shader->bindUniform("material.normal", 1);
	shader->bindUniform("material.specular", 2);
	shader->bindUniform("material.shininess", mesh->material.specularPower);
}
void Game::BindLights(const std::vector<unique_ptr<pkr::Light>>& lights, aie::ShaderProgram* shader)
{
	//Pass through amount of lights
	shader->bindUniform("NumOfLights", (int)lights.size());

	std::string uniform;
	//Pass through lights
	for (int i = 0; i < lights.size(); ++i)
	{
		//Common
		uniform = "lights[" + std::to_string(i) + "].type";
		shader->bindUniform(uniform.c_str(), lights[i]->type);

		uniform = "lights[" + std::to_string(i) + "].position";
		shader->bindUniform(uniform.c_str(), lights[i]->position);

		uniform = "lights[" + std::to_string(i) + "].direction";
		shader->bindUniform(uniform.c_str(), lights[i]->direction);

		uniform = "lights[" + std::to_string(i) + "].Ia";
		shader->bindUniform(uniform.c_str(), lights[i]->ambient);

		uniform = "lights[" + std::to_string(i) + "].Id";
		shader->bindUniform(uniform.c_str(), lights[i]->diffuse);

		uniform = "lights[" + std::to_string(i) + "].Is";
		shader->bindUniform(uniform.c_str(), lights[i]->specular);

		switch (lights[i]->type)
		{
		case pkr::LightType::SPOT:
			uniform = "lights[" + std::to_string(i) + "].cutOff";
			shader->bindUniform(uniform.c_str(), glm::cos(glm::radians(dynamic_cast<pkr::SpotLight*>(lights[i].get())->cutOff)));

			uniform = "lights[" + std::to_string(i) + "].outerCutOff";
			shader->bindUniform(uniform.c_str(), glm::cos(glm::radians(dynamic_cast<pkr::SpotLight*>(lights[i].get())->outerCutOff)));

		case pkr::LightType::OMNI:
			uniform = "lights[" + std::to_string(i) + "].constant";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->constant);

			uniform = "lights[" + std::to_string(i) + "].linear";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->linear);

			uniform = "lights[" + std::to_string(i) + "].quadratic";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->quadratic);
		}
	}
}
void Game::DrawCamera()
{
	aie::Gizmos::draw(c.camera->getProjectionView());
	aie::Gizmos::draw2D((float)getScreenWidth(), (float)getScreenHeight());
}














