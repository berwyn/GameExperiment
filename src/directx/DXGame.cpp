#include <stdio.h>
#include <dxgi.h>
#include <strsafe.h>

#include "../main/Logger.h"
#include "DXGame.h"
#include "UTFHelpers.h"

static DXGame* instance;

IGame* CreateGame()
{
	if (instance == NULL)
		instance = new DXGame();
	return instance;
}

static LRESULT CALLBACK StaticWindowHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return instance->StaticWindowProc(hwnd, uMsg, wParam, lParam);
}

bool DXGame::Init()
{
	moduleInstance = GetModuleHandle(NULL);

	bool windowClassRegistered = registerWindowClass();
	if (!windowClassRegistered) return windowClassRegistered;

	RECT rect;
	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;

	int defaultWidth = 800;
	int defaultHeight = 600;
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
		Logger::GetInstance()->Debug(&std::string("Render loop"));
	}
}

void DXGame::Terminate()
{
	DestroyWindow(windowHandle);
}

LRESULT CALLBACK DXGame::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(hwnd);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	switch (uMsg)
	{
		case WM_SIZE:
		{

		} break;

		case WM_ACTIVATEAPP:
		{

		} break;

		case WM_CLOSE:
		{
			DestroyWindow(windowHandle);
			UnregisterClass(
				windowClassName.c_str(),
				moduleInstance);
			destroyed = false;
		} break;
		
		case WM_DESTROY:
		{
			PostQuitMessage(0);
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