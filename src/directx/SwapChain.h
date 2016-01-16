#pragma once

#include <memory>
#include <Windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>

#include "Utils.h"

struct SwapChain
{
	ComPtr<IDXGIFactory1> factory;
	ComPtr<IDXGIAdapter1> adapter;
	ComPtr<IDXGIOutput1> output;
	ComPtr<ID3D11Device> device;
	ComPtr<IDXGISwapChain> swapChain;
	D3D_FEATURE_LEVEL* featureLevel;
	ComPtr<ID3D11DeviceContext> deviceContext;
};

HRESULT CreateDXGIDeviceAndAdapter(SwapChain*, HWND);
HRESULT CreateDXGISwapChain(SwapChain*, HWND);