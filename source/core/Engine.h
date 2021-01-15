#pragma once

#include "Window.h"
#include "Graphics.h"

class Engine
{
public:

	Engine(
		HINSTANCE			hInstance, 
		LPCWSTR				windowClassName, 
		const unsigned int	width, 
		const unsigned int	height, 
		bool				isFullscreen);

	~Engine();

public:

	void update();
	void render();

public:

	bool isRunning();

private:

	Window*		window		= nullptr;
	Graphics*	graphics	= nullptr;

};

