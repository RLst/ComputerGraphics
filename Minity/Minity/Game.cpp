//Tony Le
//21 Mar 2019

#include "Game.h"

#include <iostream>

#include "Gizmos.h"
#include "FlyCamera.h"
#include "Vector.h"
#include "Mesh.h"
#include "Input.h"

#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"

using namespace pkr;

Game::Game()
{
}
Game::~Game()
{
}


bool Game::Start()
{
	//Camera
	c.camera.reset(new FlyCamera(c.position, c.lookAt, c.speed, c.smoothing, c.fov, c.aspect, c.near, c.far));	//Sets initial pos
	//c.camera.reset(new FlyCamera());

	StartSolarSystem();
	//StartQuatTutorial();
	StartRenderGeomTutorial();

	return true;
}

void Game::Update()
{
	//UpdateQuatTutorial();
	UpdateCamera();
}

void Game::Draw()
{
	DrawGrid(30);
	DrawSolarSystem();
	//DrawQuatTutorial();
	DrawRenderGeomTutorial();

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
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//Load fragment shader from file
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (m_shader.link() == false) {
		printf("Shader Error: %s\n", m_shader.getLastError());
		assert(false);	//Lazy exception handling
	}
	
	//Make quad
	m_quadMesh.reset(new Mesh());
	m_quadTransform = glm::scale(vec3(15, 0, 10));
	
	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	//vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	//vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
	m_quadMesh->initialise(4, vertices, 6, indices);
	//m_quadMesh->initialiseQuad();
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
void Game::DrawGrid(int size)
{
	aie::Gizmos::addTransform(glm::mat4(1));	//Draw the little tri coloured gizmo at the centre

	if (size % 2 == 1) --size;	//round to the nearest even number
	if (size == 0) size = 2;	//protect from divide by zero
	int halfsize = size / 2;

	//Draw grid
	for (int i = 0; i <= size; ++i)
	{
		aie::Gizmos::addLine(vec3(-halfsize + i, 0, halfsize), vec3(-halfsize + i, 0, -halfsize), i == halfsize ? pkr::Colour::white() : pkr::Colour::shade(0.15f));
		aie::Gizmos::addLine(vec3(halfsize, 0, -halfsize + i), vec3(-halfsize, 0, -halfsize + i), i == halfsize ? pkr::Colour::white() : pkr::Colour::shade(0.15f));
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
	static mat4 tPlanetPos = mat4();
	tOrbitAng += 0.025f;
	//tPlanetPos = glm::mat4(1) * glm::rotate(tOrbitAng, vec3(0, 1, 0)) * glm::translate(vec3(0, 0, 10));
	tPlanetPos = glm::rotate(tOrbitAng, vec3(0, 1, 0)) * glm::translate(vec3(10, 0, 10));
	aie::Gizmos::addSphere(vec3(0), 1, 20, 20, pkr::Colour::dodgerblue(), &tPlanetPos);

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
	m_shader.bind();

	//bind transform
	auto pvm = c.camera->getProjectionView() * m_quadTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);

	//Draw Quad
	m_quadMesh->draw();
}
