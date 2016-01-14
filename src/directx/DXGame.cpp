#include <stdio.h>
#include <stdint.h>
#include <dxgi.h>
#include <strsafe.h>

#include "../main/Logger.h"
#include "../main/engine/Engine.h"

#include "DXGame.h"
#include "UTFHelpers.h"

static DXGame* instance;
static std::aligned_storage<sizeof(DXGame), alignof(DXGame)>::type dxgameStorage;

#pragma region IGAME
IGame* CreateGame(std::shared_ptr<Engine> engine)
{
	if (instance == nullptr)
	{
		instance = (DXGame*)&dxgameStorage;
		new (&dxgameStorage) DXGame(engine);
	}

	return instance;
}

DXGame::DXGame(std::shared_ptr<Engine> e)
{
	engine = e;
}

bool DXGame::Init()
{
	moduleInstance = GetModuleHandle(NULL);

	bool windowClassRegistered = registerWindowClass();
	if (!windowClassRegistered) return windowClassRegistered;

	RECT rect;
	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;

	int defaultWidth = engine->renderCanvas->width;
	int defaultHeight = engine->renderCanvas->height;
	SetRect(&rect, 0, 0, defaultWidth, defaultHeight);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	windowHandle = CreateWindowEx(
		0, windowClassName.c_str(),
		L"GameExperiment",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		x, y, width, height,
		0, NULL, moduleInstance, 0);

	if (windowHandle == NULL)
	{
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		// Display the error message and exit the process
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);

		return false;
	}

	swapChain = CreateDXGISwapChain(windowHandle);
	return true;
}

void DXGame::Loop()
{
	while (!destroyed)
	{
		MSG msg;
		while (PeekMessage(&msg, windowHandle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) destroyed = true;
		}
	}
}

void DXGame::Terminate()
{
	DestroyWindow(windowHandle);
}

#pragma endregion

#pragma region Win32

static LRESULT CALLBACK StaticWindowHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return instance->StaticWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK DXGame::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_SIZING:
		case WM_SIZE:
		{
			std::shared_ptr<Canvas> renderCanvas = engine->renderCanvas;
			std::shared_ptr<Canvas> uiCanvas = engine->uiCanvas;

			RECT windowRect;
			GetWindowRect(windowHandle, &windowRect);
			
			uint32_t width = windowRect.right - windowRect.left;
			uint32_t height = windowRect.bottom - windowRect.top;

			renderCanvas->width = width * renderCanvas->scaleFactor;
			renderCanvas->height = height * renderCanvas->scaleFactor;
			uiCanvas->width = width * uiCanvas->scaleFactor;
			uiCanvas->height = height * uiCanvas->scaleFactor;
		} break;

		case WM_ACTIVATEAPP:
		{
			engine->inForeground = wParam == TRUE;
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC devCtxt = BeginPaint(hwnd, &paint);

			int32_t x = paint.rcPaint.left;
			int32_t y = paint.rcPaint.top;
			int32_t height = paint.rcPaint.bottom - paint.rcPaint.top;
			int32_t width = paint.rcPaint.right - paint.rcPaint.left;
		} break;

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			UnregisterClass(
				windowClassName.c_str(),
				moduleInstance);
			destroyed = true;
		} break;
		
		case WM_DESTROY:
		{
			PostQuitMessage(1);
		} break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool DXGame::registerWindowClass()
{
	if (moduleInstance == NULL)
		moduleInstance = (HINSTANCE)GetModuleHandle(NULL);

	hIcon = NULL;
	WCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);

	if (hIcon == NULL)
		hIcon = ExtractIcon(moduleInstance, szExePath, 0);

	wndClass = {};
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = StaticWindowHandler;
	wndClass.hInstance = moduleInstance;
	wndClass.hIcon = hIcon;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = windowClassName.c_str();

	if (!RegisterClass(&wndClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			return false;
	}

	return true;
}

#pragma endregion
