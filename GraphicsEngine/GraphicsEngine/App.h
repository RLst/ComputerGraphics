#pragma once
#include "Time.h"

class GLFWwindow;

namespace pkr {

class Time;

class App
{
	friend class Time;
private:
	unsigned int	m_fps;

	bool			m_terminating = false;
	unsigned int	m_screenWidth;
	unsigned int	m_screenHeight;

	GLFWwindow *	m_window;

public:
	App();
	virtual ~App();		//??? Why virtual?

	int				Run(const char* windowTitle, unsigned int width, unsigned int height, bool fullscreen);
	
	//Cores
	virtual bool	Awake() = 0;
	virtual bool	Start() = 0;
	virtual void	Update() = 0;
	virtual void	Draw() = 0;
	virtual bool	End() = 0;

	//Utilities
	unsigned int	fps() const;
	unsigned int	getScreenWidth() const;
	unsigned int	getScreenHeight() const;
};

}
