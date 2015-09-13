#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <string>
#include <stdbool.h>

#include "../main/Game.hpp"

class DXGame : public IGame
{
public:
	virtual bool Init() override;
	virtual void Loop() override;
	virtual void Terminate() override;
	virtual LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	virtual bool registerWindowClass();

	HINSTANCE moduleInstance;
	HICON hIcon;
	WNDCLASS wndClass;
	HWND windowHandle;
	std::string windowClassName = "GameExperimentWndClass";
	bool destroyed = false;
};