#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string>

#include "Windows.h"
#include "../main/engine/Engine.h"
#include "../main/engine/Renderer.h"
#include "Shader/ColorShader.h"

class DXRenderer : public IRenderer
{

public:

	DXRenderer(std::shared_ptr<Engine> engine);

	bool Init(uint32_t width, uint32_t height) override;
	void Draw() override;

	LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	inline static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return instance->windowProc(hwnd, uMsg, wParam, lParam);
	};

private:

	const std::wstring windowClassName = L"GameExperimentWndClass";
	const DXGI_FORMAT dxgiFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	const uint32_t numBuffers = 2;

	static DXRenderer* instance;

	bool occluded;
	HINSTANCE moduleInstance;
	HICON icon;
	WNDCLASS windowClass;
	HWND windowHandle;
	RECT drawRect;

	ComPtr<IDXGIFactory1> factory;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIOutput> output;
	ComPtr<ID3D11Device> device;
	ComPtr<IDXGISwapChain> swapChain;
	D3D_FEATURE_LEVEL featureLevel;
	ComPtr<ID3D11DeviceContext> deviceContext;
	std::unique_ptr<ColorShader::ColorShader> colorShader;

	bool registerWindowClass();
	HRESULT createDXGIDeviceAndAdapter();
	HRESULT createDXGISwapChain();
	void fixBuffers();

};