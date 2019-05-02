#include "Time.h"
#include "App.h"
#include <GLFW/glfw3.h>

namespace pkr
{
	double Time::m_t = 0;
	double Time::m_dt = 0;	//Init static vars like this
	double Time::m_fdt = 0;

	void Time::updateTime()
	{
		m_t = glfwGetTime();
	}

	void Time::updateDeltaTime()
	{
		double nowTime;
		nowTime = glfwGetTime();
		static double prevTime = nowTime;

		m_dt = nowTime - prevTime;
		prevTime = nowTime;
	}

	double Time::time()
	{
		return m_t;
	}

	double Time::deltaTime()
	{
		return m_dt;
	}

	double Time::fixedDeltaTime()
	{
		return m_fdt;
	}

}
