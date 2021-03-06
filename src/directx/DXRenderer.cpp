#include <thread>

#include "DXRenderer.h"
#include "main/UTFHelpers.h"
#include "main/Logger.h"

DXRenderer* DXRenderer::instance;

DXRenderer::DXRenderer(std::shared_ptr<Engine> engine) : IRenderer(engine)
{
    if (instance == nullptr)
    {
        instance = this;
    }
    colorShader = std::make_unique<ColorShader::ColorShader>();
}

#pragma region Public Members

bool DXRenderer::Init(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;

    moduleInstance = GetModuleHandle(NULL);

    bool windowClassRegistered = registerWindowClass();
    if (!windowClassRegistered) return false;

    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;

    drawRect = { 0 };
    SetRect(&drawRect, 0, 0, width, height);
    AdjustWindowRect(&drawRect, WS_OVERLAPPEDWINDOW, false);

    int actualWidth = drawRect.right - drawRect.left;
    int actualHeight = drawRect.bottom - drawRect.top;

    windowHandle = CreateWindowEx(
        0, windowClassName.c_str(),
        L"GameExperiment",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        x, y, actualWidth, actualHeight,
        0, NULL, moduleInstance, 0);

    if (windowHandle == NULL)
    {
        LPTSTR lpMsgBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            lpMsgBuf,
            0, NULL);

        Logger::GetInstance()->Fatal(&std::string(CStringA(lpMsgBuf)));
        LocalFree(lpMsgBuf);
        return false;
    }

    auto hr = createDXGIDeviceAndAdapter();
    if (FAILED(hr))
    {
        return false;
    }

    hr = createDXGISwapChain();
    if (FAILED(hr))
    {
        return false;
    }

    swapChain->Present(0, 0);

    auto result = colorShader->Init(device, windowHandle);
    if (!result) { return false; }

    return true;
}

void DXRenderer::Draw(int64_t delta)
{
    using namespace std::literals;
    using namespace DirectX::PackedVector;
    using ColorShader::Data::VertexInput;

    MSG msg;
    while (PeekMessage(&msg, windowHandle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
        {
            engine->ShouldHalt = true;
        }
    }

    HRESULT hr;
    if (occluded)
    {
        hr = swapChain->Present(0, DXGI_PRESENT_TEST);
        if (hr != S_OK)
        {
            std::this_thread::sleep_for(16ms);
            return;
        }

        occluded = false;
    }

    D3D11_TEXTURE2D_DESC desc = { 0 };
    backBuffer->GetDesc(&desc);

    D3D11_VIEWPORT viewport = { 0 };
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = desc.Width;
    viewport.Height = desc.Height;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;

    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.FrontCounterClockwise = true;

    ComPtr<ID3D11RasterizerState> rasterState;
    device->CreateRasterizerState(&rasterDesc, &rasterState);

    deviceContext->OMSetRenderTargets(1, &renderTarget.p, nullptr);
    deviceContext->RSSetState(rasterState.p);
    deviceContext->RSSetViewports(1, &viewport);

    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTarget.p, clearColor);

    auto vertices = std::make_shared<std::vector<VertexInput>>();
    vertices->push_back({ XMFLOAT4(0.0f, 0.5f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) });
    vertices->push_back({ XMFLOAT4(0.45f, -0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) });
    vertices->push_back({ XMFLOAT4(-0.45f, -0.5f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) });
    colorShader->Render(deviceContext, device, vertices.get());

    hr = swapChain->Present(0, 0);

    switch (hr)
    {
    case DXGI_STATUS_OCCLUDED:
    {
        occluded = true;
    } break;

    case DXGI_STATUS_MODE_CHANGED:
    {
        fixBuffers();
    } break;

    default:
        return;
    }
}

#pragma endregion

#pragma region Private Members

bool DXRenderer::registerWindowClass()
{
    icon = NULL;
    WCHAR szExePath[MAX_PATH];
    GetModuleFileName(NULL, szExePath, MAX_PATH);

    if (icon == NULL)
    {
        icon = ExtractIcon(moduleInstance, szExePath, 0);
    }

    windowClass = { 0 };
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.lpfnWndProc = StaticWindowProc;
    windowClass.hInstance = moduleInstance;
    windowClass.hIcon = icon;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = windowClassName.c_str();

    if (!RegisterClass(&windowClass))
    {
        DWORD dwError = GetLastError();
        if (dwError != ERROR_CLASS_ALREADY_EXISTS)
            return false;
    }

    return true;
}

LRESULT DXRenderer::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SIZE:
    case WM_SIZING:
    {
        fixBuffers();
    } break;

    case WM_ACTIVATEAPP:
    {
        // TOOD: Handle window focus
    } break;

    case WM_PAINT:
    {
        // TODO: Paint
    } break;

    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        UnregisterClass(windowClassName.c_str(), moduleInstance);
        engine->ShouldHalt = true;
    } break;

    case WM_DESTROY:
    {
        PostQuitMessage(1);
    } break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HRESULT DXRenderer::createDXGIDeviceAndAdapter()
{
    auto hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory));

    if (hr != S_OK)
    {
        Logger::GetInstance()->Fatal(&std::string("Failed to create DXGIFactory"));
    }

    auto monitor = MonitorFromWindow(windowHandle, MONITOR_DEFAULTTOPRIMARY);

    ComPtr<IDXGIAdapter1> adapter;
    for (uint32_t i = 0; factory->EnumAdapters1(i, &adapter) == S_OK; i++)
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
                this->adapter = adapter;
                this->output = output;

                uint32_t flags = 0;
#ifdef DEBUG
                flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

                D3D_FEATURE_LEVEL levels[2] = {
                    D3D_FEATURE_LEVEL_11_1,
                    D3D_FEATURE_LEVEL_11_0
                };

                hr = D3D11CreateDevice(
                    adapter,
                    D3D_DRIVER_TYPE_UNKNOWN, NULL,
                    flags,
                    levels, 2,
                    D3D11_SDK_VERSION,
                    &device, &featureLevel, &deviceContext);

                return hr;
            }

            output.Release();
        }
        adapter.Release();
    }


    return E_UNEXPECTED;
}

HRESULT DXRenderer::createDXGISwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc = { 0 };

    desc.BufferDesc.Width = NULL;
    desc.BufferDesc.Height = NULL;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.Format = dxgiFormat;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    desc.SampleDesc.Count = 2;
    desc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;

    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.BufferCount = numBuffers;
    desc.OutputWindow = windowHandle;
    desc.Windowed = TRUE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    auto hr = factory->CreateSwapChain(device, &desc, &swapChain);

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
        createRenderTarget();
        return S_OK;
    }
}

void DXRenderer::createRenderTarget()
{
    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    auto hr = device->CreateRenderTargetView(backBuffer, nullptr, &renderTarget);
    if (FAILED(hr)) {
        Logger::GetInstance()->Fatal(&std::string("Failed to create render target view"));
    }
}

void DXRenderer::fixBuffers()
{
    GetWindowRect(windowHandle, &drawRect);
    this->width = drawRect.right - drawRect.left;
    this->height = drawRect.bottom - drawRect.top;

    if (swapChain != nullptr)
    {
        swapChain->ResizeBuffers(numBuffers, this->width, this->height, dxgiFormat, 0);
        createRenderTarget();
    }
}

#pragma endregion