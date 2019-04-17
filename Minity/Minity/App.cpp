//Tony Le
//21 Mar 2019

#include "App.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#include "gl_core_4_4.h"
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
#include "GLFW/glfw3.h"

#include "Time.h"
#include "Input.h"
#include "Gizmos.h"
#include <iostream>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace pkr {

	App::App() :
		m_window(nullptr),
		pm_isTerminating(false)
	{}
	App::~App() {}

	void App::WindowConfig(const char * appTitle, unsigned int screenWidth, unsigned int screenHeight, vec4 backgroundColor, bool isFullscreen)
	{
		m_appTitle = appTitle;
		m_scrnWidth = screenWidth;
		m_scrnHeight = screenHeight;
		m_bgCol = backgroundColor;
		m_isFullscreen = isFullscreen;
	}

	void App::GizmoConfig(unsigned int maxLines, unsigned int maxTris, unsigned int max2DLines, unsigned int max2DTris)
	{
		pm_maxLines = maxLines;
		pm_maxTris = maxTris;
		pm_max2DLines = max2DLines;
		pm_max2DTris = max2DTris;
	}


	int App::Run()
	{
		//INITIALISE
		auto initReturnCode = CoreInit();
		if (initReturnCode != PKR_SUCCESS)
			return initReturnCode;

		//GAME LOOP
		while (!pm_isTerminating)
		{
			//------------------- OPENGL --------------------------//
			//Skip updates and draw if window is minimized
			if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
				continue;

			//UPDATE
			CoreUpdate();

			//DRAW
			CoreDraw();

			//Check if app is terminating
			if (glfwWindowShouldClose(m_window) == GLFW_TRUE ||			//User clicks close window button
				glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	//User presses ESC
				pm_isTerminating = true;
		}

		//SHUTDOWN
		if (!CoreEnd()) return -5;

		//Successful run
		return 0;
	}


	static void glfwErrorCallback(int code, const char* msg)
	{
#ifdef _DEBUG
		std::cout << "GLFW Error " << code << ": " << msg << std::endl;
#endif
	}

	int App::CoreInit()
	{
		///------------------ PRE --------------------///
		//------------------ OPENGL --------------------/
		//https://www.glfw.org/docs/latest/quick.html
		//0. Create and set error call backs with glfwSetErrorCallback()
		//1. glfwInit() to init OpenGL
		//2. glfwCreateWindow() to create window and assign to pointer
		//3. set options using glfwWindowHint()
		//4. make the context current using glfwMakeContextcurrent()
		//5. init extention loader library ie. glewInit(), ogl_LoadFunctions(), gladGLLoader()
		//6. Optional: enable vsync using glfwSwapInterval(1)
		//7. Check window close flag with glfwWindowShouldClose()
		//8. 

		pm_frames = 0;
		pm_fpsInterval = 0;

		//Initialise GLFW
		glfwSetErrorCallback(glfwErrorCallback);
		if (glfwInit() == GLFW_FALSE)
			return -1;	//Initialisation failed

		// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

		//Create window
		m_window = glfwCreateWindow(m_scrnWidth, m_scrnHeight, m_appTitle, (m_isFullscreen ? glfwGetPrimaryMonitor() : NULL), NULL);

		if (!m_window)
		{
			glfwTerminate();
			return -2;	//Window creation failed
		}
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);	//ENABLE VSYNC

		// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
		bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
		bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
		bool err = gladLoadGL() == 0;
#else
		bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
		if (err)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
		}

		//------------------ Input manager ------------------//
		Input::create();

		//------------------- ImGui -------------------------//
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;	//whats the point of this?

		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		//Style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		//-------------------- Gizmos -----------------------//
		aie::Gizmos::create(pm_maxLines, pm_maxTris, pm_max2DLines, pm_max2DTris);

		//====================== USER =======================//

		if (!Start()) return -4;

		//===================================================//

		///-------------------- Post ------------------------/
		return PKR_SUCCESS;
	}

	void App::CoreUpdate()
	{
		///-------------------- PRE ------------------------///

		//------------------ Input manager ------------------//
		Input::getInstance()->clearStatus();

		//------------------- OPENGL --------------------------//
		glfwPollEvents();		//Update window events ie. Input etc

		//------------------ Time Manager -------------------//
		Time::updateTime();
		Time::updateDeltaTime();
		pm_fpsInterval += Time::deltaTime();
		if (pm_fpsInterval >= 1.0f)
		{
			m_fps = pm_frames;
			pm_frames = 0;
			pm_fpsInterval -= 1.0f;
		}

		//-------------------- Gizmos -------------------------//
		aie::Gizmos::clear();		//Wipe the gizmos clean for this frame

		//------------------- ImGui -------------------------//
		ImGui_ImplOpenGL3_NewFrame();	//ORDER IS CRUCIAL!!!
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		//DEMO
		if (showImGuiDemo)
			ImGui::ShowDemoWindow(&showImGuiDemo);
		//====================== USER =======================//

		Update();

		//===================================================//

		///------------------ POST --------------------///
	}

	void App::CoreDraw()
	{
		///-------------------- PRE --------------------------///
		//------------------- OPENGL --------------------------//
		//Clear screen ready for 
		glfwMakeContextCurrent(m_window);
		glfwGetFramebufferSize(m_window, &m_scrnWidth, &m_scrnHeight);
		glViewport(0, 0, m_scrnWidth, m_scrnHeight);

		glClearColor(m_bgCol.r, m_bgCol.g, m_bgCol.b, m_bgCol.a);	//Original clear
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//===================== USER ==========================//

		Draw();

		//=====================================================//

		///-------------------- POST -------------------------///		
		//--------------------- ImGui -------------------------//
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//------------------- OPENGL --------------------------//
		//Finally draw everything to screen (ie. by bringing backbuffer to the screen aka. the frontbuffer
		glfwSwapBuffers(m_window);
	}

	bool App::CoreEnd()
	{
		///-------------------- PRE --------------------------///

		//===================== USER ==========================//

		if (!End()) return false;

		//=====================================================//

		///-------------------- POST -------------------------///
		//-------------------- Gizmos -------------------------//
		aie::Gizmos::destroy();

		//--------------------- ImGui -------------------------//
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		
		//------------------- OPENGL --------------------------//
		glfwDestroyWindow(m_window);
		glfwTerminate();

		return true;
	}



	unsigned int App::getFPS() const
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
