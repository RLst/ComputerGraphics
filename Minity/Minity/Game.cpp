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

#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"

using namespace pkr;

float Game::m_specularPower = 2;

/////////// MAIN LOOP //////////////
bool Game::Start()
{
	StartLighting();

	StartPlane();			//Material and textures tutorial
	//StartFerrari();			//Direct Lighting tutorial
	//StartSoulspear();		//Advanced Texturing Tutorials
	StartAssessment();

	StartCamera();
	return true;
}

void Game::Update()
{
	UpdateObjects();
	UpdateLighting();

	UpdateCamera();
}	

void Game::Draw()
{
	DrawGridGizmo(50);

	DrawPlane();
	//DrawFerrari();
	//DrawSoulspear();
	DrawAssessment();

	DrawCamera();
}

bool Game::End()
{
	return true;
}
//////////////////////////////////////////////


//STARTS
void Game::StartPlane()
{
	//Setup shader
	m_planeShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_planeShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if (m_planeShader.link() == false)
	{
		printf("Shader Linking Error: %s\n", m_planeShader.getLastError());
		assert(false);
	}

	//Plane
	m_plane = std::make_unique<Mesh>();
	if (m_plane->texture.load("./assets/Texture/numbered_grid.tga") == false)
	{
		printf("Failed to load texture!\n");
		assert(false);
	}
	m_plane->transform = glm::scale(vec3(50));
	m_plane->initialiseQuad();
}
void Game::StartLighting()
{
	//Good light settings: diffuse = 0.95, specular = 0.12-0.2, specularPower = 0.00000001 (this shoudl have a range between 0-128. Check shader code)

	////CREATE
	//Universal ambient light (is not part of m_lights)
	m_ambientLight.diffuse = Colour::white() * 0.9f;

	//Sun
	m_lights.push_back(make_unique<DirectionalLight>());
	vec3 randomDir = vec3(Random::range(-1, 1), Random::range(-1, 1), Random::range(-1, 1));
	m_lights[0]->direction = -randomDir;
	m_lights[0]->ambient = vec3(0.5f);
	m_lights[0]->diffuse = Colour::shade(0.9f);
	m_lights[0]->specular = vec3(0.5f);

	//Point lights
	static float constant = 1.0f;
	static float minLinear = 0.25f, maxLinear = 0.8f;
	static float quadFactor = 1.8f;
	for (int i = 1; i < m_lightCount; ++i)
	{
		//Random locations around origin, random colours
		m_lights.push_back(make_unique<OmniLight>());
		static float lDist = 20;
		m_lights.back()->position = vec3(Random::range(-lDist, lDist), Random::range(0, 2), Random::range(-lDist, lDist));
		m_lights.back()->direction = vec3(0);	//Filler
		m_lights.back()->ambient = vec3(0.9f);
		m_lights.back()->diffuse = Colour::random();
		m_lights.back()->specular = vec3(1.0f);
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->constant = 1.0f;	//Always 1
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->linear = Random::range(minLinear, maxLinear);
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->quadratic = Random::range(minLinear * quadFactor, maxLinear * quadFactor);
	}

	////WET CAR LOOK
	//m_ambientLight->diffuse = glm::vec3(0.2f);
	//m_lights[0]->diffuse = glm::vec3(0.6f);
	//m_lights[0]->specular = glm::vec3(0.21f);
	//m_specularPower = 0.0001f;
}
void Game::StartFerrari()
{
	//Load shader
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		assert(false);
	}

	//Setup
	m_ferrari = std::make_unique<aie::OBJMesh>();
	m_ferrari->material.specularPower = 0.01f;
	m_ferrari->transform = glm::translate(vec3(-10, 0, -10)) * glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));

	//Load demo mesh
	if (m_ferrari->load("./assets/LaFerrari.obj") == false) {
		printf("Error loading mesh!\n");
		assert(false);
	}
	//Load demo texture
	if (m_ferrari->material.diffuseTexture.load("./assets/Texture/numbered_grid.tga") == false) {
		printf("File load error!\n");
		assert(false);
	}
}
void Game::StartSoulspear()
{
	//Load normal map texture
	m_normalmapShader = std::make_unique<aie::ShaderProgram>(); //Allocate
	m_normalmapShader->loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
	m_normalmapShader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");
	if (m_normalmapShader->link() == false) {
		printf("Error linking shader: %s\n", m_normalmapShader->getLastError()); 
		assert(false);
	}

	//Setup
	m_soulspear = std::make_unique<aie::OBJMesh>();	//Allocate
	m_soulspear->material.specularPower = 5;
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

	//Setup mesh
	m_model = make_unique<aie::OBJMesh>();
	
	m_model->material.ambient = vec3(0.1f);
	m_model->material.diffuse = vec3(0.9f);
	m_model->material.specular = vec3(0.5f);
	m_model->material.specularPower = 1.0f;
	
	m_model->transform = mat4(1) * glm::translate(vec3(0, 0, 0)) * glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));
	
	if (m_model->load("./assets/LaFerrari.obj", true, false) == false) {
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
void Game::UpdateObjects()
{
	//Adjust objects specular powers
	if (Input::getInstance()->isKeyDown(KeyCode::I))
	{
		m_specularPower += 0.01f;
		std::cout << "Specular Power: " << m_specularPower << std::endl;
	}
	if (Input::getInstance()->isKeyDown(KeyCode::K))
	{
		m_specularPower -= 0.01f;
		std::cout << "Specular Power: " << m_specularPower << std::endl;
	}
}
void Game::UpdateLighting()
{
	//query time since application started
	float t = (float)Time::time() * 0.5f;
	static float ang = 2.f;
	if (Input::getInstance()->isKeyDown(KeyCode::LeftArrow))
		ang += 0.01f;
	if (Input::getInstance()->isKeyDown(KeyCode::RightArrow))
		ang -= 0.01f;

	////Adjust light properties
	//Ambient
	if (Input::getInstance()->isKeyDown(KeyCode::T))
	{
		m_lights[0]->ambient += 0.01f;
		std::cout << "Ambient: " << m_ambientLight.diffuse[0] << std::endl;
	}
	if (Input::getInstance()->isKeyDown(KeyCode::G))
	{
		m_lights[0]->ambient -= 0.01f;
		std::cout << "Ambient: " << m_ambientLight.diffuse[0] << std::endl;
	}
	//Diffuse
	if (Input::getInstance()->isKeyDown(KeyCode::Y))
	{
		m_lights[0]->diffuse += 0.01f;
		std::cout << "Diffuse: " << m_lights[0]->diffuse[0] << std::endl;
	}
	if (Input::getInstance()->isKeyDown(KeyCode::H))
	{
		m_lights[0]->diffuse -= 0.01f;
		std::cout << "Diffuse: " << m_lights[0]->diffuse[0] << std::endl;
	}
	//Specular
	if (Input::getInstance()->isKeyDown(KeyCode::U))
	{
		m_lights[0]->specular += 0.01f;
		std::cout << "Specular: " << m_lights[0]->specular[0] << std::endl;
	}
	if (Input::getInstance()->isKeyDown(KeyCode::J))
	{
		m_lights[0]->specular -= 0.01f;
		std::cout << "Specular: " << m_lights[0]->specular[0] << std::endl;
	}

	//Move sun
	m_lights[0]->direction = glm::normalize(vec3(glm::cos(ang * 2), glm::sin(ang * 2), 0));

	//Orbit point lights around origin
	//static float lightDist = 15;
	//for (int i = 1; i < m_lights.size(); ++i)
	//{
	//	m_lights[i]->position = glm::normalize(vec3(glm::cos(t * 2) * lightDist, m_lights[i]->position.y, glm::sin(t * 2) * lightDist));
	//}
}
void Game::UpdateCamera()
{
	c.camera->update();
}


//DRAWS
void Game::DrawGridGizmo(int size)
{
	aie::Gizmos::addTransform(glm::scale(glm::vec3(2)));	//Draw the little tri coloured gizmo at the centre

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
void Game::DrawLighting()
{
	for (int i = 0; i < m_lights.size(); i++)
	{

	}
}
void Game::DrawPlane()
{
	//Shader Bindings
	m_planeShader.bind();
	m_planeShader.bindUniform("ProjectionViewModel", c.camera->getProjectionView() * m_plane->transform);

	static float intensity = 0.4f;
	m_planeShader.bindUniform("Intensity", intensity);
	m_planeShader.bindUniform("DiffuseTexture", 0);
	m_plane->texture.bind(0);
	//Draw plane
	m_plane->draw();
}
void Game::DrawFerrari()
{
	//bind shader	
	m_phongShader.bind();

	//bind transform
	m_phongShader.bindUniform("uProjectionViewModel", c.camera->getProjectionView() * m_ferrari->transform);

	//bind model matrix
	m_phongShader.bindUniform("uModel", m_ferrari->transform);


	//bind transform for lighting
	m_phongShader.bindUniform("uNormal", glm::inverseTranspose(glm::mat3(m_ferrari->transform)));
	
	//bind camera positions
	m_phongShader.bindUniform("ViewPos", c.camera->getPosition());

	//bind Light
	m_phongShader.bindUniform("Ia", m_ambientLight.diffuse);
	m_phongShader.bindUniform("Id", m_lights[0]->diffuse);
	m_phongShader.bindUniform("Is", m_lights[0]->specular);
	m_phongShader.bindUniform("LightDirection", m_lights[0]->direction);

	m_phongShader.bindUniform("specularPower", m_specularPower);
	//m_phongShader.bindUniform("specularPower", m_ferrari->material.specularPower);

	//draw object
	m_ferrari->draw();
}
void Game::DrawSoulspear()
{
	////Shader Bindings (all in order of binding)
	m_normalmapShader->bind();

	//Vertex
	m_normalmapShader->bindUniform("uProjectionViewModel", c.camera->getProjectionView() * m_soulspear->transform);
	m_normalmapShader->bindUniform("uModel", m_soulspear->transform);
	m_normalmapShader->bindUniform("uNormal", glm::inverseTranspose(glm::mat3(m_soulspear->transform)));

	//Fragment
	m_soulspear->material.diffuseTexture.bind(0);
	m_soulspear->material.normalTexture.bind(1);
	m_soulspear->material.specularTexture.bind(2);
	m_normalmapShader->bindUniform("diffuseTexture", 0);
	m_normalmapShader->bindUniform("normalTexture", 1);
	m_normalmapShader->bindUniform("specularTexture", 2);

	m_normalmapShader->bindUniform("ViewPos", c.camera->getPosition());

	m_normalmapShader->bindUniform("specularPower", m_soulspear->material.specularPower);

	m_normalmapShader->bindUniform("Ia", m_ambientLight.diffuse);
	m_normalmapShader->bindUniform("Id", m_lights[0]->diffuse);
	m_normalmapShader->bindUniform("Is", m_lights[0]->specular);
	m_normalmapShader->bindUniform("LightDirection", m_lights[0]->direction);
	
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
	BindMaterial(m_model.get(), m_shader.get());
	m_shader->bindUniform("Ks", m_lights[0]->specular);
	m_shader->bindUniform("Kd", m_lights[0]->diffuse);

	//Lights
	BindLights(m_lights, m_shader.get());

	m_model->draw();
}
void Game::DrawCamera()
{
	aie::Gizmos::draw(c.camera->getProjectionView());
	aie::Gizmos::draw2D((float)getScreenWidth(), (float)getScreenHeight());
}

void Game::BindMaterial(aie::OBJMesh* mesh, aie::ShaderProgram* shader)
{
	mesh->material.diffuseTexture.bind(0);
	mesh->material.normalTexture.bind(1);
	mesh->material.specularTexture.bind(2);

	shader->bindUniform("Ka", mesh->material.ambient);
	shader->bindUniform("material.diffuse", 0);
	shader->bindUniform("material.normal", 1);
	shader->bindUniform("material.specular", 2);
	shader->bindUniform("material.shininess", m_specularPower);	//TEST
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
		case pkr::eLightType::SPOT:
			uniform = "lights[" + std::to_string(i) + "].cutOff";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::SpotLight*>(lights[i].get())->cutOff);

			uniform = "lights[" + std::to_string(i) + "].outerCutOff";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::SpotLight*>(lights[i].get())->outerCutOff);

		case pkr::eLightType::OMNI:
			uniform = "lights[" + std::to_string(i) + "].constant";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->constant);

			uniform = "lights[" + std::to_string(i) + "].linear";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->linear);

			uniform = "lights[" + std::to_string(i) + "].quadratic";
			shader->bindUniform(uniform.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->quadratic);
		}
	}
}