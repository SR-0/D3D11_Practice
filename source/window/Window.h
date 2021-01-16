#pragma once
#include <Windows.h>

class Window
{
public:

	Window(
		HINSTANCE&   hInstance,
		LPCWSTR      windowClassName,
		unsigned int width,
		unsigned int height,
		bool         isFullscreen);

	~Window();

private:

	bool create(
		HINSTANCE&   hInstance,
		unsigned int width,
		unsigned int height,
		bool         isFullscreen);

private:

	static LRESULT CALLBACK wndProc(
		HWND   hWnd,
		UINT   uMsg,
		WPARAM wParam,
		LPARAM lParam);

public:

	int update();

public:

	HWND			getHandle();
	unsigned int	getWidth();
	unsigned int	getHeight();

private:

	WNDCLASS		windowClass		= { };
	LPCWSTR			windowClassName	= nullptr;
	HWND			handle			= nullptr;
	unsigned int	width			= 0;
	unsigned int	height			= 0;
	bool			isFullScreen	= false;

};