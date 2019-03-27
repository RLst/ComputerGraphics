//Tony Le
//21 Mar 2019

#include "Game.h"

#include <iostream>

#include "Gizmos.h"
#include "FlyCamera.h"
#include "Vector.h"

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
	m_cam.camera = new FlyCamera(m_cam.position);	//Sets initial pos
	m_cam.camera->setLookAt(m_cam.lookAt);
	m_cam.camera->setProjection(m_cam.fovAngle, m_cam.aspect, m_cam.near, m_cam.far);

	//Quaternion tutorial
	m_positions[0] = vec3(-10, 5, -10);
	m_positions[1] = vec3(10, 0, -10);
	m_positions[2] = vec3(10, 2.5f, 10);
	m_rotations[0] = quat(vec3(1, 0, 0));
	m_rotations[1] = quat(vec3(0, 1, 0));
	m_rotations[2] = quat(vec3(0, 0, 1));

	m_hipFrames[0].position = vec3(0, 5, 0);
	m_hipFrames[0].rotation = quat((vec3(1, 0, 0)));
	m_hipFrames[1].position = vec3(0, 5, 0);
	m_hipFrames[1].rotation = quat((vec3(-1, 0, 0)));
	m_kneeFrames[0].position = vec3(0, -2.5f, 0);
	m_kneeFrames[0].rotation = quat(vec3(1, 0, 0));
	m_kneeFrames[1].position = vec3(0, -2.5f, 0);
	m_kneeFrames[1].rotation = quat(vec3(0, 0, 0));
	m_ankleFrames[0].position = vec3(0, -2.5f, 0);
	m_ankleFrames[0].rotation = quat(vec3(-1, 0, 0));
	m_ankleFrames[1].position = vec3(0, -2.5f, 0);
	m_ankleFrames[1].rotation = quat(vec3(0, 0, 0));

	m_kneeBone = mat4(1);
	m_ankleBone = mat4(1);

	////Init solar system
	m_ss_angVel = 0.5f;
	//Sun
	m_planets[0].radius = 2.f;
	m_planets[0].colour = vec4(1, 0.60f, 0, 1);
	m_planets[0].pos = vec3(0,0,0);
	m_planets[0].orbital.vel = 1.f / 24;
	m_planets[0].orbital.angle = 0;

	return true;
}

void Game::Update()
{
	//Quaternion tutorial
	//use time to animate a alue between [0,1]
	float s = glm::cos((float)Time::time()) * 0.5f + 0.5f;
	box.p = (1.0f - s) * m_positions[0] + s * m_positions[1] + s * m_positions[2];

	////Flying box
	//quaternion slerp
	box.r = glm::slerp(m_rotations[0], m_rotations[1], s);
	//build a matrix
	box.m = glm::translate(box.p) * glm::toMat4(box.r);
	//Orbit the camera around
	static float angle = 0; static float rads; static float orbitDist = 35;
	angle += 0.25f;
	if (angle > 360) angle = 0;
	rads = angle * glm::pi<float>() / 180.f;

	//linearly interpolate hip position
	vec3 p = (1.0f - s) * m_hipFrames[0].position + s * m_hipFrames[0].position;

	//spherically interpolate hip rotation
	quat r = glm::slerp(m_hipFrames[0].rotation, m_hipFrames[1].rotation, s);

	//Update the hip bone
	m_hipBone = glm::translate(p) * glm::toMat4(r);
	
	////Calculate the new knee and ankle bone matrices, then concatenate as described = Parent * Child
	//Concatenate the knee bone matrix with the hip bone matrix
	m_kneeBone = m_hipBone * m_kneeBone;
	m_ankleBone = m_kneeBone * m_ankleBone;

	m_hipPos = vec3(m_hipBone[3].x, m_hipBone[3].y, m_hipBone[3].z);
	m_kneePos = vec3(m_kneeBone[3].x, m_kneeBone[3].x, m_kneeBone[3].z);
	m_anklePos = vec3(m_ankleBone[3].x, m_ankleBone[3].y, m_ankleBone[3].z);

	//Update Camera
	m_cam.camera->setPosition(vec3(glm::sin(rads) * orbitDist, 7.5f, glm::cos(rads) * orbitDist));
	//m_cam.camera->setLookAt(m_hipPos);
	m_cam.camera->update();
}

void Game::Draw()
{
	//Draw grid
	aie::Gizmos::addTransform(glm::mat4(1));	//Draw the little tri coloured gizmo at the centre
	drawGrid(30);

	////Draw solar system
	//Sun
	aie::Gizmos::addSphere(m_planets[0].pos, m_planets[0].radius, 32, 32, m_colours.sun);

	////Quaternion tutorial
	//Flying box
	vec3 legExtents(0.5f, 2.f, 0.5f);
	aie::Gizmos::addTransform(box.m);
	aie::Gizmos::addAABBFilled(box.p, vec3(0.5f), pkr::Colour::red(), &box.m);

	//Leg
	aie::Gizmos::addAABBFilled(m_hipPos, legExtents, pkr::Colour::fuschia(), &m_hipBone);
	aie::Gizmos::addAABBFilled(m_kneePos, legExtents, pkr::Colour::fuschia(), &m_kneeBone);
	aie::Gizmos::addAABBFilled(m_anklePos, legExtents, pkr::Colour::fuschia(), &m_ankleBone);

	//Temp planet
	static float tOrbitAng = 0;
	static float tOrbitRadius = 4.f;
	static mat4 tRotate = mat4();
	static mat4 tPlanetPos = mat4();
	tOrbitAng += 0.01f;

	tPlanetPos = glm::translate(tPlanetPos, vec3(glm::sin(tOrbitAng) * tOrbitRadius, 0, glm::cos(tOrbitAng) * tOrbitRadius));
	aie::Gizmos::addSphere(vec3(2,0,2), 1, 20, 20, m_colours.white, &tPlanetPos);

	//// TEMP - Engineer this into the engine so that it is hidden ////
	aie::Gizmos::draw(m_cam.camera->getProjectionView());
}

bool Game::End()
{
	delete m_cam.camera;
	return true;
}



void Game::drawGrid(int size)
{
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