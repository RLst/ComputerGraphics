//Tony Le
//21 Mar 2019

#include "Game.h"

#include <iostream>

#include "Gizmos.h"
#include "FlyCamera.h"
#include "Vector.h"
#include "Mesh.h"
#include "Input.h"
#include "OBJMesh.h"

#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"

using namespace pkr;

bool Game::Start()
{
	//Camera
	c.camera = std::make_unique<FlyCamera>(c.position, c.lookAt, c.speed, c.fov, c.aspect, c.near, c.far);
	//c.camera.reset(new FlyCamera());

	StartSolarSystem();
	//StartQuatTutorial();
	//StartRenderGeomTutorial();
	//StartMaterialAndTextures();
	StartLighting();

	return true;
}

void Game::Update()
{
	//UpdateQuatTutorial();
	UpdateLighting();
	UpdateCamera();
}

void Game::Draw()
{
	DrawGridGizmo(100);
	DrawSolarSystem();
	//DrawQuatTutorial();
	//DrawRenderGeomTutorial();
	DrawLighting();

	////Draw cameras
	aie::Gizmos::draw(c.camera->getProjectionView());
	aie::Gizmos::draw2D((float)getScreenWidth(), (float)getScreenHeight());
}

bool Game::End()
{
	return true;
}

//STARTS
void Game::StartSolarSystem()
{
	////Init solar system
	m_ss_angVel = 0.5f;
	//Sun
	m_planets[0].radius = 2.f;
	m_planets[0].colour = vec4(1, 0.60f, 0, 1);
	m_planets[0].pos = vec3(0, 0, 0);
	m_planets[0].orbital.vel = 1.f / 24;
	m_planets[0].orbital.angle = 0;
	m_planets[0].transform = glm::translate(vec3(0, 0, 0));
}
void Game::StartQuatTutorial()
{
	////Quaternion tutorial
	m_positions[0] = vec3(-10, 5, -10);
	m_positions[1] = vec3(10, 0, -10);
	m_positions[2] = vec3(10, 2.5f, 10);
	m_rotations[0] = quat(vec3(1, 0, 0));
	m_rotations[1] = quat(vec3(0, 1, 0));
	m_rotations[2] = quat(vec3(0, 0, 1));

	m_hipFrames[0].position = vec3(0, 3, 0); m_hipFrames[0].rotation = quat((vec3(1, 0, 0)));
	m_hipFrames[1].position = vec3(0, 3, 0); m_hipFrames[1].rotation = quat((vec3(-1, 0, 0)));

	m_kneeFrames[0].position = vec3(0, -1, 0); m_kneeFrames[0].rotation = quat(vec3(1, 0, 0));
	m_kneeFrames[1].position = vec3(0, -1, 0); m_kneeFrames[1].rotation = quat(vec3(0, 0, 0));

	m_ankleFrames[0].position = vec3(0, -1, 0); m_ankleFrames[0].rotation = quat(vec3(-1, 0, 0));
	m_ankleFrames[1].position = vec3(0, -1, 0); m_ankleFrames[1].rotation = quat(vec3(0, 0, 0));

	m_hipBone = mat4(1);
	m_kneeBone = mat4(1);
	m_ankleBone = mat4(1);
}
void Game::StartRenderGeomTutorial()
{
	////Rendering geometry
	//Load vertex shader from file
	m_shaderProg.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//Load fragment shader from file
	m_shaderProg.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple_diffuse.frag");

	if (m_shaderProg.link() == false)
		printf("Shader Error: %s\n", m_shaderProg.getLastError()); assert(false);	//Lazy exception handling
	
	//Mesh::Vertex vertices[4];
	//vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	//vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	//vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	//vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	////vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	////vertices[5].position = { 0.5f, 0, -0.5f, 1 };
	//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
	//m_quadMesh->initialise(4, vertices, 6, indices);

	//DEMO
	m_demoObj.reset(new aie::OBJMesh());
	if (!m_demoObj->load("./assets/LaFerrari.obj"))
		printf("Demo Mesh Error!\n"); assert(false);
	m_demoTransform = glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));
}
void Game::StartMaterialAndTextures()
{
	//m_texture1.reset(new aie::Texture());
	//m_texture1->load("./assets/Texture/interior_LOD0.bmp");
	////Create a 2x2 black n white checker texture
	////RED simply means one color channel, ie. grayscale
	//m_texture2.reset(new aie::Texture());
	//unsigned char texelData[4] = { 0, 255, 255, 0 };
	//m_texture2->create(2, 2, aie::Texture::RED, texelData);

	//QUAD
	m_planeMesh.reset(new Mesh());
	//m_planeMesh = std::make_unique<aie::OBJMesh>();
	if (m_planeTexture.load("./assets/Texture/numbered_grid.tga") == false)
		printf("Failed to load texture!\n"); assert(false);
	m_planeTransform = glm::scale(vec3(10, 0, 10));
	m_planeMesh->initialiseQuad();
}
void Game::StartLighting()
{
	//Load shader
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (!m_phongShader.link())
		printf("Shader Error: %s\n", m_phongShader.getLastError()); assert(false);

	//Load demo mesh
	m_demoObj = std::make_unique<aie::OBJMesh>();
	if (!m_demoObj->load("./assets/LaFerrari.obj"))
		printf("Mesh Error!\n"); assert(false);
	m_demoTransform = glm::rotate(-glm::pi<float>() * 0.5f, vec3(1, 0, 0)) * glm::scale(vec3(0.1f));

	//Set light position
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1, 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };
}

//UPDATES
void Game::UpdateQuatTutorial()
{
	//Quaternion tutorial
	//use time to animate a alue between [0,1]
	float oscil = glm::cos((float)Time::time()) * 0.5f + 0.5f;
	box.p = (1.0f - oscil) * m_positions[0] + oscil * m_positions[1] + oscil * m_positions[2];

	////Flying box
	//quaternion slerp
	box.r = glm::slerp(m_rotations[0], m_rotations[1], oscil);
	//build a matrix
	box.m = glm::translate(box.p) * glm::toMat4(box.r);

	//Interpolate hip bone 
	vec3 tPos = (1.0f - oscil) * m_hipFrames[0].position + oscil * m_hipFrames[1].position;
	quat tRot = glm::slerp(m_hipFrames[0].rotation, m_hipFrames[1].rotation, oscil);
	m_hipBone = glm::translate(tPos) * glm::toMat4(tRot);

	//Interpolate knee, concatenate with hip bone
	tPos = (1.0f - oscil) * m_kneeFrames[0].position + oscil * m_kneeFrames[1].position;
	tRot = glm::slerp(m_kneeFrames[0].rotation, m_kneeFrames[1].rotation, oscil);
	m_kneeBone = m_hipBone * glm::translate(vec3(0, -1, 0)) /** glm::toMat4(tRot)*/ /** glm::translate(tPos)*/;

	//Interpolate ankle, concatenate with knee bone
	tPos = (1.0f - oscil) * m_ankleFrames[0].position + oscil * m_ankleFrames[1].position;
	tRot = glm::slerp(m_ankleFrames[0].rotation, m_ankleFrames[1].rotation, oscil);
	m_ankleBone = m_kneeBone * glm::toMat4(tRot) * (glm::translate(tPos));

	m_hipPos = vec3(m_hipBone[3].x, m_hipBone[3].y, m_hipBone[3].z);
	m_kneePos = vec3(m_kneeBone[3].x, m_kneeBone[3].x, m_kneeBone[3].z);
	m_anklePos = vec3(m_ankleBone[3].x, m_ankleBone[3].y, m_ankleBone[3].z);
}
void Game::UpdateLighting()
{
	//query time since application started
	float t = Time::time();

	//Rotate light
	m_light.direction = glm::normalize(vec3(glm::cos(t * 2), glm::sin(t * 2), 0));
}
void Game::UpdateCamera()
{
	//Update Camera
	//Orbit the camera around
	//static float angle = 0; static float rads; static float orbitDist = 35;
	//angle += 0.2f;
	//if (angle > 360) angle = 0;
	//rads = angle * glm::pi<float>() / 180.f;
	//c.camera->setPosition(vec3(glm::sin(rads) * orbitDist, 7.5f, glm::cos(rads) * orbitDist));
	//c.camera->setProjection(c.fov, getScreenWidth() / (float)getScreenHeight(), c.near, c.far);	//Doesn't work very well
	c.camera->update();
}

//DRAWS
void Game::DrawGridGizmo(int size)
{
	aie::Gizmos::addTransform(glm::mat4(1));	//Draw the little tri coloured gizmo at the centre

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
void Game::DrawSolarSystem()
{
	////Draw solar system
	//Sun
	aie::Gizmos::addSphere(m_planets[0].pos, m_planets[0].radius, 32, 32, pkr::Colour::yellow(), &m_planets[0].transform);
	//aie::Gizmos::addSphere(m_planets[0].pos)

	//Temp planet
	static float tOrbitAng = 0;
	static float tOrbitRadius = 4.f;
	static mat4 tRotate = mat4();
	static mat4 tPlanetTransform = mat4();
	tOrbitAng += 0.015f;
	//tPlanetPos = glm::mat4(1) * glm::rotate(tOrbitAng, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 10));
	tPlanetTransform = glm::rotate(tOrbitAng, vec3(0, 1, 0)) * glm::translate(vec3(10, 0, 10));
	aie::Gizmos::addSphere(vec3(0), 1, 20, 20, pkr::Colour::dodgerblue(), &tPlanetTransform);

}
void Game::DrawQuatTutorial()
{
	////Quaternion tutorial
	//Flying box
	vec3 legExtents(0.5f, 0.5f, 0.5f);
	aie::Gizmos::addTransform(box.m);
	aie::Gizmos::addAABBFilled(box.p, vec3(0.5f), pkr::Colour::red(), &box.m);

	//Leg
	aie::Gizmos::addAABBFilled(m_hipPos, legExtents, pkr::Colour::fuschia(), &m_hipBone);
	aie::Gizmos::addAABBFilled(m_kneePos, legExtents, pkr::Colour::fuschia(), &m_kneeBone);
	aie::Gizmos::addAABBFilled(m_anklePos, legExtents, pkr::Colour::fuschia(), &m_ankleBone);
}
void Game::DrawRenderGeomTutorial()
{
	//bind shader
	m_shaderProg.bind();

	//bind transform
	auto pvm = c.camera->getProjectionView() * m_planeTransform;
	m_shaderProg.bindUniform("ProjectionViewModel", pvm);

	//bind texture location
	m_shaderProg.bindUniform("diffuseTexture", 0);

	//Bind texture to specified locstion
	m_planeTexture.bind(0);

	//Draw Quad
	m_planeMesh->draw();

	//bind transform
	auto pvm2 = c.camera->getProjectionView() * m_demoTransform;
	m_shaderProg.bindUniform("ProjectionViewModel", pvm2);

	//Draw demo mesh
	m_demoObj->draw();
}
void Game::DrawLighting()
{
	//bind shader	
	m_phongShader.bind();

	//bind Light
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	//bind transform
	auto pvm = c.camera->getProjectionView() * m_demoTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	//bind transform for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_demoTransform)));

	//draw object
	m_demoObj->draw();
}
