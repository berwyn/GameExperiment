#include <experimental/filesystem>

#include "../main/Logger.h"
#include "ShaderLoader.h"

namespace fs = std::experimental::filesystem;

HRESULT ShaderLoader::LoadVertex(
	ID3D11Device* device,
	const wchar_t* path,
	const D3D11_INPUT_ELEMENT_DESC* inputDesc,
	UINT inputCount,
	ID3D11VertexShader** shader,
	ID3D11InputLayout** layout)
{
	if (!shader || !layout) { return E_POINTER; }
	if (!inputDesc || !inputCount) { return E_INVALIDARG; }
	if (!path || !fs::exists(fs::current_path() / fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		HRESULT hr;
		hr = device->CreateVertexShader(data, filesize, nullptr, shader);
		if (hr != S_OK) { return hr; }
		hr = device->CreateInputLayout(inputDesc, inputCount, data, filesize, layout);
		if (hr != S_OK) { return hr; }
		return S_OK;
	});
}

HRESULT ShaderLoader::LoadHull(
	ID3D11Device* device,
	const wchar_t* path,
	ID3D11HullShader** shader)
{
	if (!shader) { return E_POINTER; }
	if (!path || !fs::exists(fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		return device->CreateHullShader(data, filesize, nullptr, shader);
	});
}

HRESULT ShaderLoader::LoadDomain(
	ID3D11Device* device,
	const wchar_t* path,
	ID3D11DomainShader** shader)
{
	if (!shader) { return E_POINTER; }
	if (!path || !fs::exists(fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		return device->CreateDomainShader(data, filesize, nullptr, shader);
	});
}

HRESULT ShaderLoader::LoadGeometry(
	ID3D11Device* device,
	const wchar_t* path,
	ID3D11GeometryShader** shader)
{
	if (!shader) { return E_POINTER; }
	if (!path || !fs::exists(fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		return device->CreateGeometryShader(data, filesize, nullptr, shader);
	});
}

HRESULT ShaderLoader::LoadPixel(
	ID3D11Device* device,
	const wchar_t* path,
	ID3D11PixelShader** shader)
{
	if (!shader) { return E_POINTER; }
	if (!path || !fs::exists(fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		return device->CreatePixelShader(data, filesize, nullptr, shader);
	});
}

HRESULT ShaderLoader::LoadCompute(
	ID3D11Device* device,
	const wchar_t* path,
	ID3D11ComputeShader** shader)
{
	if (!shader) { return E_POINTER; }
	if (!path || !fs::exists(fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		return device->CreateComputeShader(data, filesize, nullptr, shader);
	});
}