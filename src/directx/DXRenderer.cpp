#include "DXRenderer.h"
#include "UTFHelpers.h"
#include "../main/Logger.h"

// Forward declaration because c++ blows goats
DXRenderer* DXRenderer::instance;

DXRenderer::DXRenderer(Engine* engine) : IRenderer(engine)
{
	if (instance == nullptr)
	{
		instance = this;
	}
}

#pragma region Public Members

bool DXRenderer::Init(uint32_t width, uint32_t height)
{
	moduleInstance = GetModuleHandle(NULL);

	bool windowClassRegistered = registerWindowClass();
	if (!windowClassRegistered) return false;

	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;

	drawRect = { 0 };
	SetRect(&drawRect, 0, 0, width, height);
	AdjustWindowRect(&drawRect, WS_OVERLAPPEDWINDOW, false);

	int actualWidth = drawRect.right - drawRect.left;
	int actualHeight = drawRect.bottom - drawRect.top;

	windowHandle = CreateWindowEx(
		0, windowClassName.c_str(),
		L"GameExperiment",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		x, y, actualWidth, actualHeight,
		0, NULL, moduleInstance, 0);

	if (windowHandle == NULL)
	{
		LPTSTR lpMsgBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			lpMsgBuf,
			0, NULL);

		Logger::GetInstance()->Fatal(&std::string(CStringA(lpMsgBuf)));
		LocalFree(lpMsgBuf);
		return false;
	}

	return true;
}

void DXRenderer::Draw()
{
	MSG msg;
	while (PeekMessage(&msg, windowHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			engine->ShouldHalt = true;
		}
	}

	// TODO: Draw into backbuffer, then present it
}

#pragma endregion

#pragma region Private Members

bool DXRenderer::registerWindowClass()
{
	icon = NULL;
	WCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);

	if (icon == NULL)
	{
		icon = ExtractIcon(moduleInstance, szExePath, 0);
	}

	windowClass = { 0 };
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = StaticWindowProc;
	windowClass.hInstance = moduleInstance;
	windowClass.hIcon = icon;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = windowClassName.c_str();

	if (!RegisterClass(&windowClass))
	{
		DWORD dwError = GetLastError();
		if (dwError != ERROR_CLASS_ALREADY_EXISTS)
			return false;
	}

	return true;
}

LRESULT DXRenderer::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_SIZE:
		case WM_SIZING:
		{
			GetWindowRect(windowHandle, &drawRect);
		} break;

		case WM_ACTIVATEAPP:
		{
			// TOOD: Handle window focus
		} break;

		case WM_PAINT:
		{
			// TODO: Paint
		} break;

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			UnregisterClass(windowClassName.c_str(), moduleInstance);
			engine->ShouldHalt = true;
		} break;

		case WM_DESTROY:
		{
			PostQuitMessage(1);
		} break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#pragma endregion