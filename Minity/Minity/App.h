//Tony Le
//21 Mar 2019

#pragma once
#include "Time.h"

#include "glm/ext.hpp"
#include "Colour.h"

using glm::vec4;

struct GLFWwindow;

//// Prototype
#include <vector>
class GameObject;
class Component;
////

namespace pkr {

	enum eFlags
	{
		PKR_FAIL = 0,
		PKR_SUCCESS = 1,

		PKR_FALSE = 0,
		PKR_TRUE = 1,
	};

	class Input;
	class Time;

typedef class App		//TODO rename this to Engine later
{
	//very [P]rivate [M]ember variables used by core methods
	unsigned int	pm_frames;
	double			pm_fpsInterval;
	bool			pm_isTerminating = false;

	unsigned int	pm_maxLines, pm_maxTris, pm_max2DLines, pm_max2DTris;

private:
	std::vector<GameObject*> gameObjects;

	//Window
	GLFWwindow *	m_window;
	const char*		m_appTitle;
	int				m_scrnWidth, m_scrnHeight;
	vec4			m_bgCol;
	bool			m_isFullscreen;
	unsigned int	m_fps;

	//ImGui
	bool			showImGuiDemo = false;

	//Hidden core logic that needs to run to start engine
	int				CoreInit();											
	void			CoreUpdate();
	void			CoreDraw();
	bool			CoreEnd();

protected:
	void			ShowImguiDemoWindow() {	showImGuiDemo = true; }
	
public:
	App();
	virtual ~App();

	//Singleton stuff. Not copyable or [implicitly] not moveable
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	int				Run();		//Engine entry point

	//Overridable User Methods
	virtual bool	Start() = 0;	//For now is abstract/interface and must be derived
	virtual void	Update() {}
	virtual void	Draw() {}
	virtual bool	End() { return true; }

	//MUST RUN THESE TO configure the engine
	void			WindowConfig(const char* appTitle,
								unsigned int screenWidth, unsigned int screenHeight,
								vec4 backgroundColor,
								bool isFullscreen);
	void			GizmoConfig	(unsigned int maxLines, unsigned int maxTris,
								unsigned int max2DLines, unsigned int max2DTris);

	//Utility functions
	unsigned int	getFPS() const;
	unsigned int	getScreenWidth() const;
	unsigned int	getScreenHeight() const;
	GLFWwindow*		getWindow() const { return m_window; }
	vec4			getBackgroundColour() const;
	void			setBackgroundColour(const vec4& colour);
} App;

}