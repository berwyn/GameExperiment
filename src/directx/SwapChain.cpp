#include "SwapChain.h"
#include "../main/Logger.h"

HRESULT CreateDXGIDeviceAndAdapter(SwapChain* swapChain, HWND windowHandle)
{
	auto hr = CreateDXGIFactory1(IID_PPV_ARGS(&swapChain->factory));

	if (hr != S_OK)
	{
		Logger::GetInstance()->Fatal(&std::string("Failed to create DXGIFactory"));
	}

	auto monitor = MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY);

	ComPtr<IDXGIAdapter1> adapter;
	for (uint32_t i = 0; swapChain->factory->EnumAdapters1(i, &adapter) == S_OK; i++)
	{
		ComPtr<IDXGIOutput> output;
		for (uint32_t j = 0; adapter->EnumOutputs(j, &output) == S_OK; j++)
		{
			DXGI_OUTPUT_DESC desc;
			hr = output->GetDesc(&desc);
			if (FAILED(hr))
			{
				continue;
			}

			if (desc.Monitor == monitor)
			{
				swapChain->adapter = adapter;
				swapChain->output = output;
				
				hr = D3D11CreateDevice(
					swapChain->adapter,
					D3D_DRIVER_TYPE_UNKNOWN, NULL,
					NULL,
					NULL, NULL,
					D3D11_SDK_VERSION,
					&swapChain->device, &swapChain->featureLevel, &swapChain->deviceContext);

				return hr;
			}

			output.Release();
		}
		adapter.Release();
	}


	return E_UNEXPECTED;
}

HRESULT CreateDXGISwapChain(SwapChain* swapChain, HWND window)
{
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

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 2;
	desc.OutputWindow = window;
	desc.Windowed = TRUE;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	auto hr = swapChain->factory->CreateSwapChain(swapChain->device, &desc, &swapChain->swapChain);

	switch (hr)
	{
		default:
			Logger::GetInstance()->Fatal(&std::string("DXGI Failed to create swapchain."));
			return E_UNEXPECTED;
		case E_FAIL:
			Logger::GetInstance()->Fatal(&std::string("DXGI Failed to create a debug swapchain."));
			return E_UNEXPECTED;
		case E_INVALIDARG:
			Logger::GetInstance()->Fatal(&std::string("DXGI Was passed an invalid argument during swapchain creation."));
			return E_UNEXPECTED;
		case S_FALSE:
			Logger::GetInstance()->Warn(&std::string("DXGI succeeded in a nonstandard way. HERE THERE BE DRAGONS!"));
		case S_OK:
			return S_OK;
	}
}