#pragma once
#include "Time.h"

#include "glm/ext.hpp"

using glm::vec4;

class GLFWwindow;

namespace pkr {

	enum eFLAGS
	{
		PKR_FAIL = 0,
		PKR_SUCCESS = 1,

		PKR_FALSE = 0,
		PKR_TRUE = 1,
	};

class Time;

class App
{
	friend class Time;
	//friend class Camera;	//?

	//very [P]rivate [M]ember variables used by core methods
	unsigned int	pm_frames;
	double			pm_fpsInterval;
	bool			pm_isTerminating = false;

	unsigned int	pm_maxLines, pm_maxTris, pm_max2DLines, pm_max2DTris;

private:
	//Window
	const char*		m_appTitle;
	unsigned int	m_scrnWidth, m_scrnHeight;
	vec4			m_bgCol;
	bool			m_isFullscreen;

	unsigned int	m_fps;

	GLFWwindow *	m_window;

	//These hide core administrative logic that needs to run
	int				CoreInit();
	void			CoreUpdate();
	void			CoreDraw();
	bool			CoreEnd();

protected:
	void			clearScreen() const;
	
public:
	App();
	virtual ~App();		//??? Why virtual?

	//User must run these to configure the engine
	void			WindowConfig(const char* appTitle,
								unsigned int screenWidth, unsigned int screenHeight,
								vec4 backgroundColor,
								bool isFullscreen);
	void			GizmoConfig	(unsigned int maxLines, unsigned int maxTris,
								unsigned int max2DLines, unsigned int max2DTris);

	//Utility
	unsigned int	getFPS() const;
	void			showFPS() const;
	void			hideFPS() const;
	unsigned int	getScreenWidth() const;
	unsigned int	getScreenHeight() const;

	//Runs the entire engine
	int				Run();
	
	//User
	virtual bool	Start() = 0;
	virtual void	Update() = 0;
	virtual void	Draw() = 0;
	virtual bool	End() = 0;

};

}
