#include "ColorShader.h"
#include "../ShaderLoader.h"
#include "../../main/Logger.h"

bool ColorShader::ColorShader::Init(ID3D11Device* device, HWND hwnd)
{
	HRESULT hr;
	uint32_t numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	auto inputDesc = Data::GetInputDesc();
	hr = ShaderLoader::LoadVertex(
		device,
		L"assets\\shaders\\Color.vs.cso",
		&inputDesc->front(), 2,
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
	ID3D11Device* device,
	std::vector<Data::VertexInput>* input)
{
	using Data::VertexInput;

	/*bool result = setShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result) { return false; }*/

	deviceContext->IASetInputLayout(layout);
	deviceContext->VSSetShader(vertex, nullptr, NULL);
	deviceContext->PSSetShader(pixel, nullptr, NULL);

	uint32_t inputSize = sizeof(VertexInput);
	size_t numInputs = input->size();

	D3D11_BUFFER_DESC bd = { 0 };
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = inputSize * numInputs;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sData = { 0 };
	sData.pSysMem = input->data();

	ID3D11Buffer* buffer;
	device->CreateBuffer(&bd, &sData, &buffer);

	uint32_t offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &buffer, &inputSize, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->Draw(0, numInputs);

	buffer->Release();
	return true;
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