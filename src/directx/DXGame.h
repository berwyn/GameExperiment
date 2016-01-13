#pragma once

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

#include <shellapi.h>
#include <string>
#include <stdbool.h>

#include "../main/Game.h"
#include "SwapChain.h"

class DXGame : public IGame
{
public:
	DXGame(Engine*);
	virtual bool Init() override;
	virtual void Loop() override;
	virtual void Terminate() override;
	virtual LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	const std::wstring windowClassName = L"GameExperimentWndClass";


	virtual bool registerWindowClass();

	Engine* engine;
	SwapChain* swapChain;

	HINSTANCE moduleInstance;
	HICON hIcon;
	WNDCLASS wndClass;
	HWND windowHandle;

	bool destroyed = false;
};