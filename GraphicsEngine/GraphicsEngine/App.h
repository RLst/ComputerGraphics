#pragma once
#include "Time.h"

class GLFWwindow;

namespace pkr {

class Time;

class App
{
	friend class Time;
	//friend class Camera;	//?

	//Very private member variables used by core methods
	unsigned int	pm_frames;
	double			pm_fpsInterval;
	bool			pm_terminating = false;

private:
	unsigned int	m_screenWidth;
	unsigned int	m_screenHeight;
	bool			m_isFullscreen;
	const char*		m_windowTitle;

	unsigned int	m_fps;

	GLFWwindow *	m_window;

	//These hide core administrative logic that needs to run
	int				tCoreStart();
	void			tCoreUpdate();
	void			tCoreDraw();

public:
	App();
	App(const char* title, unsigned int scrnWidth, unsigned int scrnHeight, bool isFullscreen);
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
