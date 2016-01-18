#pragma once

#include <memory>

#include "Windows.h"

struct SwapChain
{
	ComPtr<IDXGIFactory1> factory;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIOutput> output;
	ComPtr<ID3D11Device> device;
	ComPtr<IDXGISwapChain> swapChain;
	D3D_FEATURE_LEVEL featureLevel;
	ComPtr<ID3D11DeviceContext> deviceContext;
};

HRESULT CreateDXGIDeviceAndAdapter(SwapChain*, HWND);
HRESULT CreateDXGISwapChain(SwapChain*, HWND);