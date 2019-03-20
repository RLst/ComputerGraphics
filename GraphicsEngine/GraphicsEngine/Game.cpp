#include "Game.h"
#include <Gizmos.h>
#include <gl_core_4_4.h>
#include <iostream>
#include "Time.h"
//#include <GLFW/glfw3.h>

Game::Game()
{
}

Game::~Game()
{
}

bool Game::Awake()
{
	return true;
}

bool Game::Start()
{
	aie::Gizmos::create(10000, 10000, 100, 100);

	//Setup camera
	m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.3f, 16 / 9.f, 0.01f, 1000.f);
	//m_projection = glm::ortho((int)getScreenWidth() / -2, (int)getScreenWidth() / 2, (int)getScreenHeight() / -2, (int)getScreenHeight() / 2, 0, 1000);

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
	std::cout << pkr::Time::deltaTime() << std::endl;
}

void Game::Draw()
{
	clearScreen(m_colours.lightGrey);
	/////// BEGIN DRAW ///////
	/////////////////////////

	aie::Gizmos::addTransform(glm::mat4(1));	//TODO what does this do?

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

	//increment solar system orbit angle
	//for (int i = 0; i < 10; ++i)
	//{

	//}
	
	///////////////////////////
	//////// DRAW END ////////
	aie::Gizmos::draw(m_projection * m_view);
}

void Game::clearScreen(const vec4& bgCol)
{
	glClearColor(bgCol.r, bgCol.g, bgCol.b, bgCol.a);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	aie::Gizmos::clear();
}

void Game::drawGrid()
{
	//Draw grid
	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? m_colours.white : m_colours.black);
		aie::Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? m_colours.white : m_colours.black);
	}
}

bool Game::End()
{
	aie::Gizmos::destroy();

	return false;
}

