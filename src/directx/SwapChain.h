#pragma once

#include <Windows.h>
#include <d3d11.h>

struct SwapChain
{
	IDXGISwapChain** swapChain;
	ID3D11Device** device;
	D3D_FEATURE_LEVEL* featureLevel;
	ID3D11DeviceContext** deviceContext;
};

SwapChain* CreateDXGISwapChain(HWND);