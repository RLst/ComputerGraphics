// Tony Le
// 14 Mar 2019

#include "Game.h"

int main()
{
	auto app = new Game();

	auto exitCode = app->Run("Minity", 1440, 900, false);

	delete app;

	return exitCode;

	/*Exitcodes:
	-1 : glfwInit failed
	-2 : Window creation failed
	-3 : OGL load functions failed
	-4 : Awake failed
	-5 : Start failed
	-6 : End failed
	*/
}








//#include <iostream>
//#include "gl_core_4_4.h"
//#include <GLFW/glfw3.h>
//
//#include <Gizmos.h>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>

//#include "imgui_glfw3.h"

//using glm::vec3;
//using glm::vec4;
//using glm::mat4;
//using aie::Gizmos;

//int main()
//{
//	if (glfwInit() == false)
//		return -1;
//	
//	GLFWwindow* window = glfwCreateWindow(1440, 900, "pokoro Graphics Engine", nullptr, nullptr);
//
//	if (window == nullptr)
//	{
//		glfwTerminate();
//		return -2;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
//	{
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return -3;
//	}
//
//	//Display versions
//	auto major = ogl_GetMajorVersion();
//	auto minor = ogl_GetMinorVersion();
//	std::cout << "GL: " << major << "." << minor << std::endl;
//
//	aie::Gizmos::create(10000, 10000, 1000, 1000);
//
//	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
//	mat4 projection = glm::perspective(glm::pi<float>() * 0.3f, 16 / 9.f, 0.01f, 1000.f);
//
//	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
//	{
//		//ImGui::Begin("TEST");
//		//ImGui::Text("testing...");
//		//ImGui::End();
//
//		glClearColor(0.25f, 0.25f, 0.25f, 1);
//		glEnable(GL_DEPTH_TEST);
//		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		Gizmos::clear();
//
//		Gizmos::addTransform(glm::mat4(1));
//
//		vec4 white(1);
//		vec4 black(0, 0, 0, 1);
//		vec4 sunCol(1, 0.65f, 0, 1);
//		//mat4 sunPos(1, 2, 3, 4,
//		//	5, 6, 7, 8,
//		//	9, 10, 11, 12,
//		//	13, 14, 15, 16);
//
//		//Draw grid
//		for (int i = 0; i < 21; ++i)
//		{
//			Gizmos::addLine(vec3(-10 + i, 0, 10),
//							vec3(-10 + i, 0, -10),
//							i == 10 ? white : black);
//			Gizmos::addLine(vec3(10, 0, -10 + i),
//							vec3(-10, 0, -10 + i),
//							i == 10 ? white : black);
//		}
//
//		//Draw sun
//		Gizmos::addSphere(vec3(0, 0, 0), 2.f, 42, 42, sunCol);
//
//		//Draw mercury
//
//		//Draw venus
//
//		//Draw earth
//
//
//		Gizmos::draw(projection * view);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	   
//	//Destroy gizmos
//	Gizmos::destroy();
//
//	//Shutdown
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
