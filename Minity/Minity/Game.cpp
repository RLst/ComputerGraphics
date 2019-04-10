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

/////////// MAIN LOOP //////////////
bool Game::Start()
{
	//StartSolarSystem();
	//StartQuatTutorial();
	//StartRenderGeomTutorial();

	StartLighting();

	StartPlane();			//Material and textures tutorial
	//StartFerrari();			//Direct Lighting tutorial
	StartSoulspear();		//Advanced Texturing Tutorials
	StartAssessment();

	StartCamera();
	return true;
}

void Game::Update()
{
	//UpdateQuatTutorial();

	UpdateObjects();
	UpdateLighting();

	UpdateCamera();
}	

void Game::Draw()
{

	//DrawSolarSystem();
	//DrawQuatTutorial();
	//DrawRenderGeomTutorial();

	DrawGridGizmo(50);

	DrawPlane();
	//DrawFerrari();
	DrawSoulspear();
	DrawAssessment();

	DrawCamera();
}

bool Game::End()
{
	return true;
}
//////////////////////////////////////////////

void Game::StartCamera()
{
	c.camera = std::make_unique<FlyCamera>(c.position, c.lookAt, c.speed, c.fov, c.aspect, c.near, c.far);
}
//STARTS
//void Game::StartSolarSystem()
//{
//	////Init solar system
//	m_ss_angVel = 0.5f;
//	//Sun
//	m_planets[0].radius = 2.f;
//	m_planets[0].colour = vec4(1, 0.60f, 0, 1);
//	m_planets[0].pos = vec3(0, 0, 0);
//	m_planets[0].orbital.vel = 1.f / 24;
//	m_planets[0].orbital.angle = 0;
//	m_planets[0].transform = glm::translate(vec3(0, 0, 0));
//}
//void Game::StartQuatTutorial()
//{
//	////Quaternion tutorial
//	m_positions[0] = vec3(-10, 5, -10);
//	m_positions[1] = vec3(10, 0, -10);
//	m_positions[2] = vec3(10, 2.5f, 10);
//	m_rotations[0] = quat(vec3(1, 0, 0));
//	m_rotations[1] = quat(vec3(0, 1, 0));
//	m_rotations[2] = quat(vec3(0, 0, 1));
//
//	m_hipFrames[0].position = vec3(0, 3, 0); m_hipFrames[0].rotation = quat((vec3(1, 0, 0)));
//	m_hipFrames[1].position = vec3(0, 3, 0); m_hipFrames[1].rotation = quat((vec3(-1, 0, 0)));
//
//	m_kneeFrames[0].position = vec3(0, -1, 0); m_kneeFrames[0].rotation = quat(vec3(1, 0, 0));
//	m_kneeFrames[1].position = vec3(0, -1, 0); m_kneeFrames[1].rotation = quat(vec3(0, 0, 0));
//
//	m_ankleFrames[0].position = vec3(0, -1, 0); m_ankleFrames[0].rotation = quat(vec3(-1, 0, 0));
//	m_ankleFrames[1].position = vec3(0, -1, 0); m_ankleFrames[1].rotation = quat(vec3(0, 0, 0));
//
//	m_hipBone = mat4(1);
//	m_kneeBone = mat4(1);
//	m_ankleBone = mat4(1);
//}
//void Game::StartRenderGeomTutorial()
//{
//	////Rendering geometry
//	//Load vertex shader from file
//	m_shaderProg.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
//
//	//Load fragment shader from file
//	m_shaderProg.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simplediffuse.frag");
//
//	if (m_shaderProg.link() == false)
//		printf("Shader Error: %s\n", m_shaderProg.getLastError()); assert(false);	//Lazy exception handling
//	
//	//Mesh::Vertex vertices[4];
//	//vertices[0].position = { -0.5f, 0, 0.5f, 1 };
//	//vertices[1].position = { 0.5f, 0, 0.5f, 1 };
//	//vertices[2].position = { -0.5f, 0, -0.5f, 1 };
//	//vertices[3].position = { 0.5f, 0, -0.5f, 1 };
//	////vertices[4].position = { 0.5f, 0, 0.5f, 1 };
//	////vertices[5].position = { 0.5f, 0, -0.5f, 1 };
//	//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
//	//m_quadMesh->initialise(4, vertices, 6, indices);
//
//	//DEMO
//	m_ferrari = std::make_unique<aie::OBJMesh>();
//	if (!m_ferrari->load("./assets/LaFerrari.obj"))
//		printf("Demo Mesh Error!\n"); assert(false);
//	m_ferrari->transform = glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));
//}
void Game::StartPlane()
{
	//Setup shader
	m_shaderProg.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_shaderProg.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if (m_shaderProg.link() == false)
	{
		printf("Shader Linking Error: %s\n", m_shaderProg.getLastError());
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

	//Load shader
	m_shader = make_unique<aie::ShaderProgram>();
	m_shader->loadShader(aie::eShaderStage::VERTEX, "./shaders/comprehensive.vert");
	m_shader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/comprehensive.frag");
	if (m_shader->link() == false)
	{
		printf("Shader Error: %s\n", m_shader->getLastError());
		assert(false);
	}

	////CREATE
	//Universal ambient light (is not part of m_lights)
	m_ambientLight = make_unique<AmbientLight>();
	m_ambientLight->diffuse = Colour::orange() * 0.4f;

	//Sun
	m_lights.push_back(make_unique<DirectionalLight>());
	vec3 randomDir = vec3(Random::range(-1, 1), Random::range(-1, 1), Random::range(-1, 1));
	m_lights.back()->direction = -randomDir;
	m_lights.back()->ambient = vec3(0.05f);
	m_lights.back()->diffuse = Colour::orange() * 0.8f;
	m_lights.back()->specular = vec3(0.5f);

	//Point lights
	static float constant = 1.0f;
	static float minLinear = 0.25f, maxLinear = 0.8f;
	static float quadFactor = 1.8f;
	for (int i = 1; i < m_lightCount; ++i)
	{
		//Random locations around origin, random colours
		m_lights.push_back(make_unique<OmniLight>());
		m_lights.back()->position = vec3(Random::range(-5, 5), Random::range(0, 2), Random::range(-5, 5));
		m_lights.back()->ambient = vec3(0.05f);
		m_lights.back()->diffuse = Colour::random();
		m_lights.back()->specular = vec3(1.0f);
		dynamic_cast<pkr::OmniLight*>(m_lights.back().get())->constant = 1.0f;
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
	m_soulspear->transform = mat4(1);

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
	m_shader->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/comprehensive.frag");
	if (m_shader->link() == false) {
		printf("Error linking shader: %s\n", m_shader->getLastError());
		assert(false);
	}

	//Setup mesh
	if (m_ferrari.get() != nullptr)  m_ferrari = make_unique<aie::OBJMesh>();
	m_ferrari->material.specularPower = 256;
	m_ferrari->transform = glm::translate(vec3(-10, 0, -10)) * glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));
	if (m_ferrari->load("./assets/LaFerrari.obj", true, true) == false) {
		printf("Error loading mesh!\n");
		assert(false);
	}

	//Load textures
	if (m_ferrari->material.diffuseTexture.load("./assets/Texture/numbered_grid.tga") == false) {
		printf("Error loading diffuse texture!\n");
		assert(false);
	}
	//if (m_ferrari->material.specularTexture.load("./assets/Texture/soulspear_specular.tga") == false) {
	//	printf("Error loading specular texture!\n");
	//	assert(false);
	//}
	//if (m_ferrari->material.normalTexture.load("./assets/Texture/soulspear_normal.tga") == false) {
	//	printf("Error loading normal texture!\n");
	//	assert(false);
	//}
}

//UPDATES
//void Game::UpdateQuatTutorial()
//{
//	//Quaternion tutorial
//	//use time to animate a alue between [0,1]
//	float oscil = glm::cos((float)Time::time()) * 0.5f + 0.5f;
//	box.p = (1.0f - oscil) * m_positions[0] + oscil * m_positions[1] + oscil * m_positions[2];
//
//	////Flying box
//	//quaternion slerp
//	box.r = glm::slerp(m_rotations[0], m_rotations[1], oscil);
//	//build a matrix
//	box.m = glm::translate(box.p) * glm::toMat4(box.r);
//
//	//Interpolate hip bone 
//	vec3 tPos = (1.0f - oscil) * m_hipFrames[0].position + oscil * m_hipFrames[1].position;
//	quat tRot = glm::slerp(m_hipFrames[0].rotation, m_hipFrames[1].rotation, oscil);
//	m_hipBone = glm::translate(tPos) * glm::toMat4(tRot);
//
//	//Interpolate knee, concatenate with hip bone
//	tPos = (1.0f - oscil) * m_kneeFrames[0].position + oscil * m_kneeFrames[1].position;
//	tRot = glm::slerp(m_kneeFrames[0].rotation, m_kneeFrames[1].rotation, oscil);
//	m_kneeBone = m_hipBone * glm::translate(vec3(0, -1, 0)) /** glm::toMat4(tRot)*/ /** glm::translate(tPos)*/;
//
//	//Interpolate ankle, concatenate with knee bone
//	tPos = (1.0f - oscil) * m_ankleFrames[0].position + oscil * m_ankleFrames[1].position;
//	tRot = glm::slerp(m_ankleFrames[0].rotation, m_ankleFrames[1].rotation, oscil);
//	m_ankleBone = m_kneeBone * glm::toMat4(tRot) * (glm::translate(tPos));
//
//	m_hipPos = vec3(m_hipBone[3].x, m_hipBone[3].y, m_hipBone[3].z);
//	m_kneePos = vec3(m_kneeBone[3].x, m_kneeBone[3].x, m_kneeBone[3].z);
//	m_anklePos = vec3(m_ankleBone[3].x, m_ankleBone[3].y, m_ankleBone[3].z);
//}
void Game::UpdateCamera()
{
	c.camera->update();
}
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
	//Make adjustments
	//m_ferrari->material.specularPower = glm::clamp(m_ferrari->material.specularPower, 0.00000000001f, 128.f);
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
		m_ambientLight->diffuse += 0.01f;
		std::cout << "Ambient: " << m_ambientLight->diffuse[0] << std::endl;
	}
	if (Input::getInstance()->isKeyDown(KeyCode::G))
	{
		m_ambientLight->diffuse -= 0.01f;
		std::cout << "Ambient: " << m_ambientLight->diffuse[0] << std::endl;
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
	for (int i = 1; i < m_lights.size(); ++i)
	{
		m_lights[i]->position = glm::normalize(vec3(glm::cos(t * 2), m_lights[i]->position.y, vec3(glm::sin(t * 2))));
	}
}


//DRAWS
void Game::DrawCamera()
{
	aie::Gizmos::draw(c.camera->getProjectionView());
	aie::Gizmos::draw2D((float)getScreenWidth(), (float)getScreenHeight());
}
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
//void Game::DrawSolarSystem()
//{
//	////Draw solar system
//	//Sun
//	aie::Gizmos::addSphere(m_planets[0].pos, m_planets[0].radius, 32, 32, pkr::Colour::yellow(), &m_planets[0].transform);
//	//aie::Gizmos::addSphere(m_planets[0].pos)
//
//	//Temp planet
//	static float tOrbitAng = 0;
//	static float tOrbitRadius = 4.f;
//	static mat4 tRotate = mat4();
//	static mat4 tPlanetTransform = mat4();
//	tOrbitAng += 0.015f;
//	//tPlanetPos = glm::mat4(1) * glm::rotate(tOrbitAng, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 10));
//	tPlanetTransform = glm::rotate(tOrbitAng, vec3(0, 1, 0)) * glm::translate(vec3(10, 0, 10));
//	aie::Gizmos::addSphere(vec3(0), 1, 20, 20, pkr::Colour::dodgerblue(), &tPlanetTransform);
//
//}
//void Game::DrawQuatTutorial()
//{
//	////Quaternion tutorial
//	//Flying box
//	vec3 legExtents(0.5f, 0.5f, 0.5f);
//	aie::Gizmos::addTransform(box.m);
//	aie::Gizmos::addAABBFilled(box.p, vec3(0.5f), pkr::Colour::redpure(), &box.m);
//
//	//Leg
//	aie::Gizmos::addAABBFilled(m_hipPos, legExtents, pkr::Colour::fuschia(), &m_hipBone);
//	aie::Gizmos::addAABBFilled(m_kneePos, legExtents, pkr::Colour::fuschia(), &m_kneeBone);
//	aie::Gizmos::addAABBFilled(m_anklePos, legExtents, pkr::Colour::fuschia(), &m_ankleBone);
//}
//void Game::DrawRenderGeomTutorial()
//{
//	//bind shader
//	m_shaderProg.bind();
//
//	//bind transform
//	auto pvm = c.camera->getProjectionView() * m_plane->transform;
//	m_shaderProg.bindUniform("ProjectionViewModel", pvm);
//
//	//bind texture location
//	m_shaderProg.bindUniform("DiffuseTexture", 0);
//
//	//Bind texture to specified locstion
//	m_planeTexture.bind(0);
//
//	//Draw Quad
//	m_plane->draw();
//}
void Game::DrawPlane()
{
	//Shader Bindings
	m_shaderProg.bind();
	m_shaderProg.bindUniform("ProjectionViewModel", c.camera->getProjectionView() * m_plane->transform);
	m_shaderProg.bindUniform("DiffuseTexture", 0);
	m_plane->texture.bind(0);
	//Draw plane
	m_plane->draw();
}
void Game::DrawFerrari()
{
	//bind shader	
	m_phongShader.bind();

	//bind Light
	m_phongShader.bindUniform("Ia", m_ambientLight->diffuse);
	m_phongShader.bindUniform("Id", m_lights[0]->diffuse);
	m_phongShader.bindUniform("Is", m_lights[0]->specular);
	m_phongShader.bindUniform("LightDirection", m_lights[0]->direction);
	m_phongShader.bindUniform("SpecularPower", m_specularPower);

	//bind camera positions
	m_phongShader.bindUniform("CameraPosition", c.camera->getPosition());

	//bind transform
	m_phongShader.bindUniform("ProjectionViewModel", c.camera->getProjectionView() * m_ferrari->transform);

	//bind model matrix
	m_phongShader.bindUniform("ModelMatrix", m_ferrari->transform);

	//bind transform for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_ferrari->transform)));

	//draw object
	m_ferrari->draw();
}
void Game::DrawSoulspear()
{
	////Shader Bindings (all in order of binding)
	m_normalmapShader->bind();

	//Vertex
	m_normalmapShader->bindUniform("ProjectionViewModel", c.camera->getProjectionView() * m_soulspear->transform);
	m_normalmapShader->bindUniform("ModelMatrix", m_soulspear->transform);
	m_normalmapShader->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_soulspear->transform)));

	//Fragment
	m_soulspear->material.diffuseTexture.bind(0);
	m_soulspear->material.normalTexture.bind(1);
	m_soulspear->material.specularTexture.bind(2);
	m_normalmapShader->bindUniform("DiffuseTexture", 0);
	m_normalmapShader->bindUniform("NormalTexture", 1);
	m_normalmapShader->bindUniform("SpecularTexture", 2);

	m_normalmapShader->bindUniform("CameraPosition", c.camera->getPosition());

	m_normalmapShader->bindUniform("SpecularPower", m_soulspear->material.specularPower);

	m_normalmapShader->bindUniform("Ia", m_ambientLight->diffuse);
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
	m_shader->bindUniform("Model", m_ferrari->transform);
	m_shader->bindUniform("View", c.camera->getView());
	m_shader->bindUniform("Projection", c.camera->getProjection());
	///Fragment
	m_shader->bindUniform("ViewPos", c.camera->getPosition());
	//Material
	BindMaterial(m_ferrari.get(), m_shader.get(), m_specularPower);
	//Lights
	BindLights(m_lights, m_shader.get());

	m_ferrari->draw();
}


static void BindMaterial(aie::OBJMesh* const mesh, aie::ShaderProgram* const shader, float shininess)
{
	mesh->material.diffuseTexture.bind(0);
	mesh->material.normalTexture.bind(1);
	mesh->material.specularTexture.bind(2);

	shader->bindUniform("material.Kd", 0);
	shader->bindUniform("material.Ks", 2);
	shader->bindUniform("material.Kn", 1);
	shader->bindUniform("material.shininess", shininess);
}

static void BindLights(const std::vector<unique_ptr<pkr::Light>>& lights, aie::ShaderProgram* const shader) 
{
	//Pass through amount of lights
	shader->bindUniform("NumOfLights", (int)lights.size());

	std::string input;
	//Pass through lights
	for (int i = 0; i < lights.size(); ++i)
	{
		//Common
		input = "Lights[" + std::to_string(i) + "].type";
		shader->bindUniform(input.c_str(), lights[i]->type);

		input = "Lights[" + std::to_string(i) + "].position";
		shader->bindUniform(input.c_str(), lights[i]->position);

		input = "Lights[" + std::to_string(i) + "].direction";
		shader->bindUniform(input.c_str(), lights[i]->direction);

		input = "Lights[" + std::to_string(i) + "].Ia";
		shader->bindUniform(input.c_str(), lights[i]->ambient);

		input = "Lights[" + std::to_string(i) + "].Id";
		shader->bindUniform(input.c_str(), lights[i]->diffuse);

		input = "Lights[" + std::to_string(i) + "].Is";
		shader->bindUniform(input.c_str(), lights[i]->specular);

		switch (lights[i]->type)
		{
		case pkr::eLightType::SPOT:
			input = "Lights[" + std::to_string(i) + "].cutOff";
			shader->bindUniform(input.c_str(), dynamic_cast<pkr::SpotLight*>(lights[i].get())->cutOff);

			input = "Lights[" + std::to_string(i) + "].outerCutOff";
			shader->bindUniform(input.c_str(), dynamic_cast<pkr::SpotLight*>(lights[i].get())->outerCutOff);

		case pkr::eLightType::OMNI:
			input = "Lights[" + std::to_string(i) + "].constant";
			shader->bindUniform(input.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->constant);

			input = "Lights[" + std::to_string(i) + "].linear";
			shader->bindUniform(input.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->linear);

			input = "Lights[" + std::to_string(i) + "].quadratic";
			shader->bindUniform(input.c_str(), dynamic_cast<pkr::OmniLight*>(lights[i].get())->quadratic);
			break;
		}
	}
}


////Jared's code... REVIEW!
//int lightLocation = m_shader->getUniform("lights");
//const int numFieldsPerLight = 2;
//for (int i = 0; i < (int)m_lights.size(); ++i)
//{
//	auto& nextLight = m_lights[i];

//	int nextLightLocation = lightLocation + numFieldsPerLight * i;

//	m_shader->bindUniform(nextLightLocation, nextLight->diffuse);
//	m_shader->bindUniform(nextLightLocation+1, nextLight->direction);

//	lights[i]->bindUniform(const aie::ShaderProgram& shaderProgram);
//}