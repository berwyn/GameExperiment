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

template<typename T>
using ComPtr = ATL::CComPtr<T>;