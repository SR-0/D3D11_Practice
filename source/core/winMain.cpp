#include "Engine.h"

int WINAPI wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PWSTR     pCmdLine,
	_In_     int       nCmdShow)
{
	LPCWSTR            wndClassName = L"Sample Window Class";
	const unsigned int width        = 800;
	const unsigned int height       = 600;

	Engine engine(hInstance, wndClassName, width, height, false);
	
	while (engine.isRunning())
	{
		engine.update();
		engine.render();
	}
}