#include "App.h"
#include "Time.h"

#include <iostream>

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>

namespace pkr {

App::App() :
	m_window(nullptr),
	m_terminating(false)
{}

App::~App() {}

int App::Run(const char * windowTitle, unsigned int width, unsigned int height, bool fullscreen)
{
	//Vars
	unsigned int frames = 0;
	double fpsInterval = 0;

	//Initialise GLFW
	if (!glfwInit())
		return -1;

	//Create window
	m_window = glfwCreateWindow(width, height, windowTitle, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (!m_window)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(m_window);

	//Fix up openGL extentions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}

#ifdef _DEBUG
	//Display version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL version: %i.%i", major, minor);
#endif // _DEBUG

	//USER INITIALISATIONS
	if (!Awake()) return -4;
	if (!Start()) return -5;

	//Game Loop
	while (!m_terminating)
	{
		//Calculate time and fps stuff
		Time::updateDeltaTime();
		fpsInterval += Time::deltaTime();
		if (fpsInterval >= 1.0f)
		{
			m_fps = frames;
			frames = 0;
			fpsInterval -= 1.0f;
		}

		//Update window events ie. Input etc
		glfwPollEvents();

		//Skip if window is minimized
		if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
			continue;

		//USER ACTIONS
		Update();
		Draw();

		//Send redrawn backbuffer to the monitor
		glfwSwapBuffers(m_window);

		//Check if app is terminating
		if (glfwWindowShouldClose(m_window) == GLFW_TRUE ||		//User closes window
			glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	//User presses ESC
			m_terminating = true;
	}

	//USER SHUTDOWN
	if (!End()) return -6;

	//Shutdown GLFW
	glfwDestroyWindow(m_window);
	glfwTerminate();
	return 0;
}

unsigned int App::fps() const
{
	return m_fps;
}

unsigned int App::getScreenWidth() const
{
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return w;
}

unsigned int App::getScreenHeight() const
{
	int w = 0, h = 0;
	glfwGetWindowSize(m_window, &w, &h);
	return h;
}

}
