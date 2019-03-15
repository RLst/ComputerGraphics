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

	m_view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(1, 1, 0));
	m_projection = glm::perspective(glm::pi<float>() * 0.3f, 16 / 9.f, 0.01f, 1000.f);

	//Sun
	m_planets[0].radius = 2.f;
	m_planets[0].colour = vec4(1, 0.60f, 0, 1);
	m_planets[0].pos = vec3(0,0,0);
	m_planets[0].orbital.vel = 1.f / 24;
	m_planets[0].orbital.angle;

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

	aie::Gizmos::addTransform(glm::mat4(1));

	drawGrid();

	////Draw solar system
	//increment solar system orbit angle
	m_ss_angle++;
	for (int i = 0; i < 10; ++i)
	{
		aie::Gizmos::addSphere(m_planets, 2.f, 32, 32, m_colours.sun);

	}

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
