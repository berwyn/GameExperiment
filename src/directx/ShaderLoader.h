#pragma once

#include "Windows.h"

template <typename Func>
static HRESULT WithMapped(const wchar_t* path, Func &&f)
{
	auto fileHandle = CreateFile(
		path, GENERIC_READ, FILE_SHARE_READ, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		auto err = GetLastError();
		return HRESULT_FROM_WIN32(err);
	}

	auto mapHandle = CreateFileMapping(
		fileHandle, nullptr, PAGE_READONLY, 0, 0, nullptr);

	if (mapHandle == nullptr)
	{
		auto err = GetLastErr();
		CloseHandle(fileHandle);
		return HRESULT_FROM_WIN32(err);
	}

	LARGE_INTEGER filesize = { 0 };
	GetFileSizeEx(fileHandle, &filesize);

	auto memory = MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, filesize.QuadPart);

	if (memory == nullptr)
	{
		auto err = GetLastErr();
		CloseHandle(mapHandle);
		CloseHandle(fileHandle);
		return HRESULT_FROM_WIN32(err);
	}

	auto hr = f((const BYTE*)memory, filesize.QuadPart);

	UnmapViewOfFile(memory);
	CloseHandle(mapHandle);
	CloseHandle(fileHandle);

	return hr;
}

class ShaderLoader
{

public:

	HRESULT LoadVertex(
		ID3D11Device* device,
		const wchar_t* path,
		const D3D11_INPUT_ELEMENT_DESC* inputDesc,
		UINT inputCount,
		ID3D11VertexShader** shader,
		ID3D11InputLayout** layout);

	HRESULT LoadHull(
		ID3D11Device* device,
		const wchar_t* path, 
		ID3D11HullShader** shader);

	HRESULT LoadDomain(
		ID3D11Device* device,
		const wchar_t* path, 
		ID3D11DomainShader** shader);

	HRESULT LoadGeometry(
		ID3D11Device* device,
		const wchar_t* path,
		ID3D11GeometryShader** shader);

	HRESULT LoadPixel(
		ID3D11Device* device,
		const wchar_t* path,
		ID3D11PixelShader** shader);

	HRESULT LoadCompute(
		ID3D11Device* device,
		const wchar_t* path,
		ID3D11ComputeShader** shader);

};