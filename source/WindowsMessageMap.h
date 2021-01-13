#pragma once

#include <unordered_map>
#include <Windows.h>

class WindowsMessageMap
{
public:

	WindowsMessageMap();

public:

	std::string operator()(DWORD msg, LPARAM lParam, WPARAM wParam) const;

public:

	std::unordered_map<DWORD, std::string> map;

};

