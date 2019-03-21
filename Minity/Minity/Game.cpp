#include "Game.h"

#include <iostream>

#include "Gizmos.h"

using namespace pkr;

Game::Game()
{
}
Game::~Game()
{
}




bool Game::Start()
{
	//Setup camera
	m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	//m_view = glm::inverse(m_view);
	m_projection = glm::perspective(glm::pi<float>() * 0.3f, 16 / 9.f, 0.01f, 1000.f);
	//m_projection = glm::ortho((int)getScreenWidth() / -2, (int)getScreenWidth() / 2, (int)getScreenHeight() / -2, (int)getScreenHeight() / 2, 0, 1000);

	////// USER START START //////
	////Init solar system
	m_ss_angVel = 0.5f;
	//Sun
	m_planets[0].radius = 2.f;
	m_planets[0].colour = vec4(1, 0.60f, 0, 1);
	m_planets[0].pos = vec3(0,0,0);
	m_planets[0].orbital.vel = 1.f / 24;
	m_planets[0].orbital.angle = 0;
	////// USER START END //////////


	return true;
}

void Game::Update()
{
	std::cout << pkr::Time::deltaTime() << std::endl;
}

void Game::Draw()
{
	////// USER DRAW START //////////
	aie::Gizmos::addTransform(glm::mat4(1));	//Draw the little tri coloured gizmo at the centre

	drawGrid();

	////Draw solar system
	//Sun
	aie::Gizmos::addSphere(m_planets[0].pos, m_planets[0].radius, 32, 32, m_colours.sun);

	//Temp planet
	static float tOrbitAng = 0;
	static float tOrbitRadius = 4.f;
	static mat4 tRotate = mat4();
	static mat4 tPlanetPos = mat4();
	tOrbitAng += 0.01f;

	tPlanetPos = glm::translate(tPlanetPos, vec3(glm::sin(tOrbitAng) * tOrbitRadius, 0, glm::cos(tOrbitAng) * tOrbitRadius));
	aie::Gizmos::addSphere(vec3(2,0,2), 1, 20, 20, m_colours.white, &tPlanetPos);

	//////// USER DRAW END ////////
	aie::Gizmos::draw(m_projection * m_view);
}

bool Game::End()
{

	return true;
}




void Game::drawGrid()
{
	//Draw grid
	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? m_colours.white : m_colours.black);
		aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? m_colours.white : m_colours.black);
	}
	glm::abs(1234);
}