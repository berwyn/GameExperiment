#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string>

#include "Windows.h"
#include "../main/engine/Engine.h"

class DXRenderer : public IRenderer
{

public:

	DXRenderer(Engine* engine);

	bool Init(uint32_t width, uint32_t height) override;
	void Draw() override;

	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	const std::wstring windowClassName = L"GameExperimentWndClass";
	static DXRenderer* instance;

	HINSTANCE moduleInstance;
	HICON icon;
	WNDCLASS windowClass;
	HWND windowHandle;
	RECT drawRect;

	bool registerWindowClass();
	LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};