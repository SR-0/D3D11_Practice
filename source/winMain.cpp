#include "Window.h"
#include "D3DInterface.h"

int WINAPI wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     PWSTR     pCmdLine,
	_In_     int       nCmdShow)
{
	LPCWSTR            wndClassName = L"Sample Window Class";
	const unsigned int width        = 800;
	const unsigned int height       = 600;

	{
		Window* window = new Window(hInstance, wndClassName, nCmdShow, width, height, false);
		D3DInterface* d3dInterface = new D3DInterface(window);
		window->messageLoop(d3dInterface);
	}
}