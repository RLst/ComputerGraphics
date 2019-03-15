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

bool App::Run(const char * windowTitle, unsigned int width, unsigned int height, bool fullscreen)
{
	//Timing
	double prevTime = glfwGetTime();
	double nowTime = 0;
	App::m_time.deltaTime = 0;
	unsigned int frames = 0;
	double fpsInterval = 0;

	//Initialise GLFW
	if (!glfwInit())
		return false;

	//Create window
	m_window = glfwCreateWindow(width, height, windowTitle, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (!m_window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_window);

	//Fix up openGL extentions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

#ifdef _DEBUG
	//Display version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL version: %i.%i", major, minor);
#endif // _DEBUG

	//USER INITIALISATIONS
	Awake();
	Start();

	//Game Loop
	while (!m_terminating)
	{
		//Calculate time and fps stuff
		nowTime = glfwGetTime();
		App::m_time.deltaTime = nowTime - prevTime;
		prevTime = nowTime;
		frames++;
		fpsInterval += App::m_time.deltaTime;
		if (fpsInterval >= 1.0f)
		{
			App::m_time.fps = frames;
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
		if (glfwWindowShouldClose(m_window) ||
			glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
			m_terminating = true;
	}

	//USER SHUTDOWN
	End();

	//Shutdown GLFW
	glfwDestroyWindow(m_window);
	glfwTerminate();
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
