#pragma once

#include <stdbool.h>
#include <memory>
#include <vector>

#include "../Windows.h"

using namespace DirectX;

namespace ColorShader
{

	namespace Data
	{
		static inline std::shared_ptr<std::vector<D3D11_INPUT_ELEMENT_DESC>> GetInputDesc()
		{
			auto desc = std::vector<D3D11_INPUT_ELEMENT_DESC>();

			D3D11_INPUT_ELEMENT_DESC pos = { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			D3D11_INPUT_ELEMENT_DESC col = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 };

			desc.push_back(pos);
			desc.push_back(col);
			desc.shrink_to_fit();

			return std::make_shared<std::vector<D3D11_INPUT_ELEMENT_DESC>>(desc);
		}

		struct VertexInput
		{
			XMFLOAT4 Position;
			XMFLOAT4 Color;
		};
	}

	class ColorShader
	{

	public:

		bool Init(
			ID3D11Device* device,
			HWND hwnd);

		bool Render(
			ID3D11DeviceContext* deviceContext,
			ID3D11Device* device,
			std::vector<Data::VertexInput>* input);

	private:

		struct MatrixBuffer
		{
			XMMATRIX worldMatrix;
			XMMATRIX viewMatrix;
			XMMATRIX projectionMatrix;
		};

		ComPtr<ID3D11VertexShader> vertex;
		ComPtr<ID3D11PixelShader> pixel;
		ComPtr<ID3D11InputLayout> layout;
		ComPtr<ID3D11Buffer> matrixBuffer;

		bool setShaderParameters(
			ID3D11DeviceContext* device,
			CXMMATRIX worldMatrix,
			CXMMATRIX viewMatrix,
			CXMMATRIX projectionMatrix);

	};
}