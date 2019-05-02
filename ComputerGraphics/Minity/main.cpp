// Tony Le
// 14 Mar 2019

#include "Game.h"
#include "Colour.h"

int main()
{
	//Initialize main app and configure settings
	auto game = new Game();
	//auto game = Game::instance();

	game->WindowConfig("Computer Graphics OpenGL App", 1440, 900, pkr::Colour::shade(0.3f), false);
	game->GizmoConfig(10000, 10000, 10000, 10000);

	//Run it
	auto exitCode = game->Run();

	//Cleanup
	delete game;

	//Error codes
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
