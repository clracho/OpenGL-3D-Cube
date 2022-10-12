#include "World.h"
#include <Cube3D/Input/InputSystem.h>
#include <iostream>

int main() {

	try
	{
		World game;
		game.run();
		InputSystem::create();
	}
	catch (const std::exception& e)
	{
		std::wclog << e.what() << std::endl;
		return 1;
	}

	InputSystem::release();

	return 0;
}