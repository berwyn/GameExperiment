#include "ColorShader.h"
#include "../ShaderLoader.h"

bool ColorShader::ColorShader::Init(ID3D11Device* device, HWND hwnd)
{
	HRESULT hr;
	uint32_t numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	hr = ShaderLoader::LoadVertex(
		device, 
		L"assets\\shaders\\Color.vs.cso", 
		Data::GetInputDesc()->data(), 2,
		&vertex, &layout);

	if (FAILED(hr)) { return false; }

	hr = ShaderLoader::LoadPixel(
		device,
		L"assets\\shaders\\Color.ps.cso",
		&pixel);

	if (FAILED(hr)) { return false; }
}

bool ColorShader::ColorShader::Render(
	ID3D11DeviceContext* deviceContext,
	CXMMATRIX worldMatrix,
	CXMMATRIX viewMatrix,
	CXMMATRIX projectionMatrix,
	Data::VertexInput input)
{
	bool result = setShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result) { return false; }

	deviceContext->IASetInputLayout(layout);
	deviceContext->VSSetShader(vertex, NULL, NULL);
	deviceContext->PSSetShader(pixel, NULL, NULL);
}

bool ColorShader::ColorShader::setShaderParameters(
	ID3D11DeviceContext* deviceContext,
	CXMMATRIX worldMatrix,
	CXMMATRIX viewMatrix,
	CXMMATRIX projectionMatrix)
{
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	uint32_t bufferNumber;

	auto world = XMMatrixTranspose(worldMatrix);
	auto view = XMMatrixTranspose(viewMatrix);
	auto projection = XMMatrixTranspose(projectionMatrix);

	hr = deviceContext->Map(matrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedResource);
	if (FAILED(hr)) { return false; }

	MatrixBuffer* dataPtr = (MatrixBuffer*)mappedResource.pData;
	dataPtr->worldMatrix = world;
	dataPtr->viewMatrix = view;
	dataPtr->projectionMatrix = projection;

	ID3D11Buffer* buffers[] = { matrixBuffer };
	deviceContext->Unmap(matrixBuffer, NULL);
	deviceContext->VSSetConstantBuffers(0, 1, &matrixBuffer.p);

	return true;
}