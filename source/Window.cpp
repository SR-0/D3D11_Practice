#include "Window.h"

#include <string>
#include "WindowsMessageMap.h"
#include "D3DInterface.h"

Window::Window(
	HINSTANCE&   hInstance, 
	LPCWSTR      wndClassName, 
	int          nCmdShow,
	unsigned int width,
	unsigned int height,
	bool         isFullscreen)
	:
	wndClassName(wndClassName),
	width(width),
	height(height)
{
	initialize(hInstance, nCmdShow, width, height, isFullscreen);
}

Window::~Window()
{
}

bool Window::initialize(
	HINSTANCE&   hInstance,
	int          nCmdShow,
	unsigned int width,
	unsigned int height,
	bool         isFullscreen)
{
	wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = wndProc;
	wndClass.cbClsExtra    = NULL;
	wndClass.cbWndExtra    = NULL;
	wndClass.hInstance     = hInstance;
	wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor       = LoadCursorW(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wndClass.lpszMenuName  = NULL;
	wndClass.lpszClassName = wndClassName;

	if (!RegisterClass(&wndClass))
	{
		MessageBoxEx(0, L"Window Initialization - Failed", L"Error", MB_OK, CAL_GREGORIAN_XLIT_ENGLISH);
		return false;
	}

	hWnd = CreateWindowEx(
		0,									// optional window styles
		wndClassName,						// window class
		L"Learn to Program with Windows",	// window text
		WS_OVERLAPPEDWINDOW,				// window style
		0,									// window position - top
		0, 									// window position - left
		width, 								// window size - width
		height, 							// window size - height
		NULL,								// parent Window
		NULL,								// menu
		hInstance,							// instance handle
		NULL								// additional application data
	);


	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);
	MoveWindow(hWnd, (desktop.right / 2) - (width / 2), (desktop.bottom / 2) - (height / 2), width, height, true);

	if (!hWnd)
	{
		MessageBoxEx(0, L"Window Creation - Failed", L"Error", MB_OK, CAL_GREGORIAN_XLIT_ENGLISH);
		return false;
	}

	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	return true;
}

LRESULT Window::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	{
		static WindowsMessageMap mm;
		OutputDebugStringA(mm(uMsg, lParam, wParam).c_str());
	}

	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					if (MessageBoxEx(0, L"Are you sure you want to exit?", L"Really?", MB_YESNO | MB_ICONQUESTION, CAL_GREGORIAN_XLIT_ENGLISH) == IDYES)
					{
						DestroyWindow(hWnd);
					}
				}
				break;

				case 'F': // tis silly
				{
					SetWindowTextA(hWnd, "Respect");
				}
				break;
			}
		}
		break;

		case WM_KEYUP:
		{
			switch (wParam)
			{
				case 'F': // tis silly
				{
					SetWindowTextA(hWnd, "No Respect");
				}
				break;
			}
		}
		break;

		case WM_PAINT:
		{
			PAINTSTRUCT paintStruct;
			HDC handleDeviceContext = BeginPaint(hWnd, &paintStruct);
			
			{
				FillRect(handleDeviceContext, &paintStruct.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
				EndPaint(hWnd, &paintStruct);
			}
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int Window::messageLoop(class D3DInterface* d3dInterface)
{
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // check if windows message exists
		{
			if (msg.message == WM_QUIT) // if WM_QUIT, exit message loop
				break;

			TranslateMessage(&msg); // translate the message
			DispatchMessage(&msg);  // send the message to default windows procedure
		}
		else if (d3dInterface != nullptr)
		{
			d3dInterface->updateScene();
			d3dInterface->drawScene();
		}
	}

	return (int)msg.wParam;
}

HWND Window::getHandle()
{
	return hWnd;
}

unsigned int Window::getWidth()
{
	return width;
}

unsigned int Window::getHeight()
{
	return height;
}
