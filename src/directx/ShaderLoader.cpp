#include <experimental/filesystem>

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
	if (!path || !fs::exists(fs::path(path))) { return E_INVALIDARG; }

	return WithMapped(path, [&](const BYTE* data, uint64_t filesize) -> HRESULT
	{
		HRESULT hr;
		hr = device->CreateVertexShader(data, filesize, nullptr, shader);
	});
}