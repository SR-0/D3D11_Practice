#include "Engine.h"

Engine::Engine(
	HINSTANCE			hInstance,
	LPCWSTR				windowClassName,
	const unsigned int	width,
	const unsigned int	height,
	bool				isFullscreen)
{
	window		= new Window(hInstance, windowClassName, width, height, false);
	graphics	= new Graphics(window);
}

Engine::~Engine()
{
	delete window;
	delete graphics;
}

void Engine::update()
{
	window->update();
	graphics->update();
}

void Engine::render()
{
	graphics->render();
}

bool Engine::isRunning()
{
	return true; // add/modify return conditions soon
}
