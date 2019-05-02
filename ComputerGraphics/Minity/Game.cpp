//Tony Le
//21 Mar 2019

#include "Game.h"

#include "Math.h"
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

//--------------- MAIN LOOP -----------------
bool Game::Start()
{
	//Init Input manager
	//m_input = Input::getInstance();

	CreateAndSetupLighting();
	InitGroundPlane();
	InitSoulspear();		//Advanced Texturing Tutorials
	InitDemoScene();
	InitCamera();
	return true;
}

void Game::Update()
{
	UpdateLighting();
	UpdateCamera();
}

void Game::Draw()
{
	if (m_lights[0] != NULL)
		setBackgroundColour(vec4(m_lights[0]->diffuse, 1));

	DrawGrid(50);
	DrawLightingGizmos();
	DrawPlane();
	DrawSoulspear();
	DrawDemoScene();
	DrawCamera();
}

bool Game::End()
{
	return true;
}
//-----------------------------------------------


//STARTS
void Game::CreateAndSetupLighting()
{
	float sunColor = 0.15f;
	float constant = 1.0f;		//Spot light constant
	float linear = 0.190f;
	float lin2quadFactor = 1.5f;		//Factor to multiply linear value of spot light by to get the quadratic value
	float cutOff, outerCutOff;

	//---- Sun ----
	for (int i = 0; i < m_dirLightCount; ++i)
	{
		m_lights.push_back(make_unique<DirectionalLight>());
		m_lights.back()->direction = vec3(0.5, -0.5, -0.5);
		m_lights.back()->position = vec3(-7.5f, 7.5f, 7.5f);
		m_lights.back()->ambient = m_lights.back()->diffuse = m_lights.back()->specular = vec3(sunColor);
	}

	//---- Omni Lights ----
	//Red
	m_lights.push_back(make_unique<OmniLight>(constant, linear, linear * lin2quadFactor));
	m_lights.back()->position = vec3(-2.5f, 1.1f, 2.55f);
	m_lights.back()->ambient = m_lights.back()->diffuse = m_lights.back()->specular = vec3(0.91f, 0.316f, 0.316f);
	
	//Green
	linear = 0.3f;
	m_lights.push_back(make_unique<OmniLight>(constant, linear, linear * lin2quadFactor));
	m_lights.back()->position = vec3(2.7f, 2.1f, 3.7f);
	m_lights.back()->ambient = m_lights.back()->diffuse = m_lights.back()->specular = vec3(0.5f, 1.f, 0.277f);

	//---- Spot lights ----
	//Blue
	linear = 0.072f;
	cutOff = pkr::Math::DegsToRads(25.f);
	outerCutOff = pkr::Math::DegsToRads(35.f);
	m_lights.push_back(make_unique<SpotLight>(constant, linear, linear * lin2quadFactor, cutOff, outerCutOff));
	m_lights.back()->position = vec3(5, 3.6f, -3.7f);
	m_lights.back()->direction = vec3(-0.776f, -0.62f, 0.115f);
	m_lights.back()->ambient = m_lights.back()->diffuse = m_lights.back()->specular = vec3(0, 0.644f, 1.0f);

	//Purple
	linear = 0.211;
	cutOff = pkr::Math::DegsToRads(15.f);
	outerCutOff = pkr::Math::DegsToRads(17.f);
	m_lights.push_back(make_unique<SpotLight>(constant, linear, linear * lin2quadFactor, cutOff, outerCutOff));
	m_lights.back()->position = vec3(0.034f, 6, 2.483f);
	m_lights.back()->direction = vec3(0, -1, 0);
	m_lights.back()->ambient = m_lights.back()->diffuse = m_lights.back()->specular = vec3(0.675f, 0, 1.0f);
}

void Game::InitGroundPlane()
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
void Game::InitSoulspear()
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
void Game::InitDemoScene()
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
}
void Game::InitCamera()
{
	c.camera = make_unique<FlyCamera>(c.position, c.lookAt, c.speed, c.fov, c.aspect, c.near, c.far);
}

//UPDATES
void Game::UpdateLighting()
{
	Input* input = Input::getInstance();

	//query time since application started
	float t = (float)Time::time() * 0.5f;

	//Draw GUI
	ImGui::Begin("Computer Graphics");
	{
		//Instructions
		ImGui::TextColored(ImVec4(1, 0.5, 0, 1), "Edit light position and direction");
		ImGui::TextWrapped("> Select a light to modify (click on light label)");
		ImGui::TextWrapped("> Choose edit mode: [Z] None [X] Position [C] Direction");
		ImGui::TextWrapped("> Adjust XZ axes: [Left Click] + [Move Mouse]");
		ImGui::TextWrapped("> Adjust Y axis: [Left Click] + [Shift]");
		ImGui::TextColored(ImVec4(1, 0.5, 0, 1), "Camera controls");
		ImGui::TextWrapped("> Free Look: [Right Click] OR [Space] + [Move Mouse]");
		ImGui::TextWrapped("> Fly [WASD]; Fly Up/Down [QE]; Faster [Shift]; Slower [Ctrl]");
		ImGui::Separator();

		//Edit Mode
		///Hotkeys
		if (input->wasKeyPressed(pkr::KeyCode::Z)) edit.mode = -1;
		else if (input->wasKeyPressed(pkr::KeyCode::X)) edit.mode = 0;
		else if (input->wasKeyPressed(pkr::KeyCode::C)) edit.mode = 1;
		///GUI
		ImGui::Text("Edit Mode: ");
		ImGui::RadioButton("None", &edit.mode, -1); ImGui::SameLine();
		ImGui::RadioButton("Position", &edit.mode, 0); ImGui::SameLine();
		ImGui::RadioButton("Direction", &edit.mode, 1);
		ImGui::Separator();
		
		//Simplified colours
		ImGui::Checkbox("Simplified Colors", &edit.simplifiedColours);
		ImGui::Separator();

		//Display a control panel section for each light
		for (int i = 0; i < m_lights.size(); ++i)
		{
			ImGui::PushID(i);	//Required otherwise each imgui control will be linked together

			//Display light number and type of light
			char label[32];
			sprintf_s(label, "Light %d", i);
			if (ImGui::Selectable(label, edit.currentLight == i)) edit.currentLight = i;
			ImGui::SameLine();
			switch (m_lights[i]->type)
			{
			case LightType::DIRECTIONAL: ImGui::Text("Directional"); break;
			case LightType::OMNI: ImGui::Text("Omni"); break;
			case LightType::SPOT: ImGui::Text("Spot"); break;
			}

			//Display light modifiables on GUI Panel
			///Position
			ImGui::SliderFloat3("Position", glm::value_ptr(m_lights[i]->position), -gui.positionRange, gui.positionRange);
			///Direction
			if (m_lights[i]->type != LightType::OMNI)
				ImGui::SliderFloat3("Direction", glm::value_ptr(m_lights[i]->direction), -1.0f, 1.0f);
			if (edit.simplifiedColours)
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
				//!!!----------- ALSO AUTO ADJUST QUADRATIC -----------//
				dynamic_cast<OmniLight*>(m_lights[i].get())->RecalcQuadraticValue();

				ImGui::Text("Constant: %f", dynamic_cast<OmniLight*>(m_lights[i].get())->constant);
				ImGui::SliderFloat("Linear", &dynamic_cast<OmniLight*>(m_lights[i].get())->linear, gui.omni.minLinear, gui.omni.maxLinear);
				ImGui::SliderFloat("Quadratic", &dynamic_cast<OmniLight*>(m_lights[i].get())->quadratic, gui.omni.minQuad, gui.omni.maxQuad);
			}
			if (m_lights[i]->type == LightType::SPOT)
			{
				ImGui::SliderAngle("Cut Off", &dynamic_cast<SpotLight*>(m_lights[i].get())->cutOff, 0, gui.spot.maxAngle);
				ImGui::SliderAngle("Outer Cut Off", &dynamic_cast<SpotLight*>(m_lights[i].get())->outerCutOff, 0, gui.spot.maxAngle);
			}

			ImGui::Separator();

			ImGui::PopID();

			//------------- Logic that actually edits the lights ------------------------//
			if (i == edit.currentLight)
			{
				if (input->isMouseButtonDown(pkr::Mouse0) && !ImGui::IsMouseHoveringAnyWindow())
				{
					//Disable cursor upon editing
					glfwSetInputMode(getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

					float xInput = 0, yInput = 0, zInput = 0;
					if (input->isKeyDown(pkr::LeftShift))
					{
						yInput = input->getMouseDeltaY() * edit.speedFactor;
					}
					else
					{
						xInput = input->getMouseDeltaX() * edit.speedFactor;
						zInput = input->getMouseDeltaY() * edit.speedFactor;
					}

					if (edit.mode == 0)	//Position
					{
						m_lights[edit.currentLight]->position.x += xInput * glm::cos(c.camera->getRotation().y) + zInput * glm::sin(c.camera->getRotation().y);
						m_lights[edit.currentLight]->position.y += yInput;
						m_lights[edit.currentLight]->position.z -= zInput * glm::cos(c.camera->getRotation().y) - xInput * glm::sin(c.camera->getRotation().y);
					}
					else if (edit.mode == 1)	//Direction
					{
						m_lights[edit.currentLight]->direction.x += xInput * glm::cos(c.camera->getRotation().y) + zInput * glm::sin(c.camera->getRotation().y);
						m_lights[edit.currentLight]->direction.y += yInput;
						m_lights[edit.currentLight]->direction.z -= zInput * glm::cos(c.camera->getRotation().y) - xInput * glm::sin(c.camera->getRotation().y);
						m_lights[edit.currentLight]->direction = glm::normalize(m_lights[edit.currentLight]->direction);
					}
				}
				else if (input->isMouseButtonUp(pkr::Mouse0))
				{
					//Re-enable cursor 
					glfwSetInputMode(getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
			}
		}
	}
	ImGui::End();
}
void Game::UpdateCamera()
{
	c.camera->update();
}

//DRAWS
void Game::DrawGrid(int size)
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

	//Draw
	m_soulspear->draw();
}
void Game::DrawDemoScene()
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

		//Extra properties for spot and omni lights
		switch (lights[i]->type)
		{
		case pkr::LightType::SPOT:
			uniform = "lights[" + std::to_string(i) + "].cutOff";
			shader->bindUniform(uniform.c_str(), glm::cos(dynamic_cast<pkr::SpotLight*>(lights[i].get())->cutOff));

			uniform = "lights[" + std::to_string(i) + "].outerCutOff";
			shader->bindUniform(uniform.c_str(), glm::cos(dynamic_cast<pkr::SpotLight*>(lights[i].get())->outerCutOff));

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














