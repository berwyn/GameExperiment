#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "Windows.h"

class ColorShaderData
{
public:

	ColorShaderData();
	~ColorShaderData();
	ColorShaderData(const ColorShaderData&);

	bool Init(ID3D11Device* device);
	void Render(ID3D11DeviceContext* context);
	uint32_t GetIndexCount();

private:

	struct VertexType
	{
		DirectX::XMVECTOR position;
		DirectX::XMVECTOR color;
	};

	ComPtr<ID3D11Buffer> vertexBuffer, indexBuffer;
	uint32_t vertexCount, indexCount;

	bool InitBuffers(ID3D11Device* device);
	void RenderBuffers(ID3D11DeviceContext* context);

};