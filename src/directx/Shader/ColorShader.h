#pragma once

#include <stdbool.h>

#include "../Windows.h"
#include "../../shader/Color.h"

using namespace DirectX;

namespace ColorShader
{
	class ColorShader
	{

	public:

		bool Init(
			ID3D11Device* device,
			HWND hwnd);

		bool Render(
			ID3D11DeviceContext* deviceContext,
			CXMMATRIX worldMatrix,
			CXMMATRIX viewMatrix,
			CXMMATRIX projectionMatrix,
			Data::VertexInput input);

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