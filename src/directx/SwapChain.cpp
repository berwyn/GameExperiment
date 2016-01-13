#include "SwapChain.h"
#include "../main/Logger.h"

SwapChain* CreateDXGISwapChain(HWND window)
{
	UINT flags = NULL;

	DXGI_SWAP_CHAIN_DESC desc = {
		{
			NULL, NULL,
			{60, 1},
			DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
			DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
			DXGI_MODE_SCALING_UNSPECIFIED
		},
		{ 2, D3D11_STANDARD_MULTISAMPLE_PATTERN },
		DXGI_USAGE_SHADER_INPUT,
		3,
		window,
		FALSE,
		DXGI_SWAP_EFFECT_DISCARD
	};

#if DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
	flags |= D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

	SwapChain swapChain = {};
	HRESULT result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE, NULL,
		flags,
		NULL, NULL,
		D3D11_SDK_VERSION,
		&desc,
		swapChain.swapChain, swapChain.device,
		swapChain.featureLevel, swapChain.deviceContext);

	switch (result)
	{
		default:
			Logger::GetInstance()->Fatal(&std::string("DXGI Failed to create swapchain."));
			break;
		case E_FAIL:
			Logger::GetInstance()->Fatal(&std::string("DXGI Failed to create a debug swapchain."));
			break;
		case E_INVALIDARG:
			Logger::GetInstance()->Fatal(&std::string("DXGI Was passed an invalid argument during swapchain creation."));
			break;
		case S_FALSE:
			Logger::GetInstance()->Warn(&std::string("DXGI succeeded in a nonstandard way. HERE THERE BE DRAGONS!"));
		case S_OK:
			return &swapChain;
	}
}