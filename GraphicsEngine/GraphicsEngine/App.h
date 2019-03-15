#pragma once
#include "Time.h"

class GLFWwindow;

namespace pkr {

class Time;

class App
{
	friend class Time;
private:
	static struct {
		unsigned int fps = 0;
		double deltaTime = 0;
		double fixedDeltaTime = 0;
	} m_time;
	
	/*static*/ double m_dt;

	bool			m_terminating = false;
	unsigned int	m_screenWidth;
	unsigned int	m_screenHeight;

	GLFWwindow *	m_window;

public:
	App();
	virtual ~App();		//??? Why virtual?

	bool	Run(const char* windowTitle, unsigned int width, unsigned int height, bool fullscreen);
	
	//Cores
	virtual bool	Awake() = 0;
	virtual bool	Start() = 0;
	virtual void	Update() = 0;
	virtual void	Draw() = 0;
	virtual bool	End() = 0;

	//Utilities
	unsigned int	getScreenWidth() const;
	unsigned int	getScreenHeight() const;

};

}
