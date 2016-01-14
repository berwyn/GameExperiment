#include "SwapChain.h"
#include "../main/Logger.h"

std::shared_ptr<SwapChain> CreateDXGISwapChain(HWND window)
{
	UINT flags = NULL;

	DXGI_SWAP_CHAIN_DESC desc = { 0 };

	desc.BufferDesc.Width = NULL;
	desc.BufferDesc.Height = NULL;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	desc.SampleDesc.Count = 2;
	desc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;

	desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	desc.BufferCount = 2;
	desc.OutputWindow = window;
	desc.Windowed = FALSE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

#if DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
	flags |= D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

	SwapChain swapChain = { 0 };
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
			return std::make_shared<SwapChain>(swapChain);
	}
}