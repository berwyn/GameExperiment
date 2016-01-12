#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <shellapi.h>
#include <string>
#include <stdbool.h>

#include "../main/Game.h"

class DXGame : public IGame
{
public:
	virtual bool Init() override;
	virtual void Loop() override;
	virtual void Terminate() override;
	virtual LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	const std::wstring windowClassName = L"GameExperimentWndClass";

	virtual bool registerWindowClass();

	HINSTANCE moduleInstance;
	HICON hIcon;
	WNDCLASS wndClass;
	HWND windowHandle;

	bool destroyed = false;
};