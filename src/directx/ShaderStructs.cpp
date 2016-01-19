#include "ShaderStructs.h"

ColorShaderData::ColorShaderData()
{
	vertexBuffer = 0;
	indexBuffer = 0;
}

ColorShaderData::ColorShaderData(const ColorShaderData& other) {}
ColorShaderData::~ColorShaderData(){}

bool ColorShaderData::Init(ID3D11Device* device)
{
	auto result = InitBuffers(device);
	if (!result)
	{
		return false;
	}
	return true;
}

void ColorShaderData::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);
}

uint32_t ColorShaderData::GetIndexCount()
{
	return indexCount;
}

bool ColorShaderData::InitBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	uint32_t* indices;


	D3D11_BUFFER_DESC vertexBufferDesc = { 0 }, indexBufferDesc = { 0 };
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(uint32_t) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData = { 0 }, indexData = { 0 };
	vertexData.pSysMem = vertices;
	indexData.pSysMem = indices;

	HRESULT hr;
	vertexCount = 3;
	indexCount = 3;

	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Bottom-left
	vertices[0].position = { -1.0f, -1.0f, 0.0f };
	vertices[0].color = { 0.0f, 1.0f, 0.0f, 1.0f };

	// Top-middle
	vertices[1].position = { 0.0f, 1.0f, 0.0f };
	vertices[1].color = { 0.0f, 1.0f, 0.0f, 1.0f };

	// Bottom-right
	vertices[2].position = { 1.0f, -1.0f, 0.0f };
	vertices[2].color = { 0.0f, 1.0f, 0.0f, 1.0f };

	indices = new uint32_t[indexCount];
	if (!indices)
	{
		return false;
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	// release arrays now that data copied into buffers
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ColorShaderData::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	uint32_t stride = sizeof(VertexType);;
	uint32_t offset = 0;
}