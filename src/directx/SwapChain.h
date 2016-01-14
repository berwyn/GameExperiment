#pragma once

#include <memory>
#include <Windows.h>
#include <d3d11.h>

#include "Utils.h"

struct SwapChain
{
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11Device> device;
	ComPtr<D3D_FEATURE_LEVEL> featureLevel;
	ComPtr<ID3D11DeviceContext> deviceContext;
};

std::shared_ptr<SwapChain> CreateDXGISwapChain(HWND);