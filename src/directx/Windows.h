#pragma once

// Windows includes, with the lean flags
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

// Win32
#include <Windows.h>
#include <shellapi.h>

// ATL
#include <atlbase.h>
#include <atlstr.h>

// DXGI
#include <d3d11.h>
#include <dxgi1_2.h>
#include <DirectXMath.h>

// Libs
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "shell32.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")

template<typename T>
using ComPtr = ATL::CComPtr<T>;