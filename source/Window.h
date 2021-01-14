#pragma once
#include <Windows.h>

class Window
{
public:

	Window(
		HINSTANCE&   hInstance,
		LPCWSTR      wndClassName,
		int          nCmdShow,
		unsigned int width,
		unsigned int height,
		bool         isFullscreen);

	~Window();

private:

	bool initialize(
		HINSTANCE&   hInstance,
		int          nCmdShow,
		unsigned int width,
		unsigned int height,
		bool         isFullscreen);

public:

	static LRESULT CALLBACK wndProc(
		HWND   hWnd,
		UINT   uMsg,
		WPARAM wParam,
		LPARAM lParam);

public:

	int  messageLoop(class D3DInterface* d3dInterface = nullptr);

public:

	HWND			getHandle();
	unsigned int	getWidth();
	unsigned int	getHeight();

private:

	WNDCLASS		wndClass		= { };
	LPCWSTR			wndClassName	= nullptr;
	HWND			hWnd			= nullptr;
	unsigned int	width			= 0;
	unsigned int	height			= 0;
	bool			isFullScreen	= false;

};