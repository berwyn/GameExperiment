#ifdef __cplusplus

#pragma once
#define SEMANTICS(semantic)
#define CBUFFER struct

#else

#define SEMANTICS(semantic) : semantic
#define CBUFFER cbuffer

#endif

#ifdef __cplusplus

#include <memory>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

namespace ColorShader
{
	namespace Data
	{
		using float4 = DirectX::XMFLOAT4;
		using matrix = DirectX::XMMATRIX;

#endif

#ifdef __cplusplus
		static std::shared_ptr<std::vector<D3D11_INPUT_ELEMENT_DESC>> GetInputDesc()
		{
			auto desc = std::vector<D3D11_INPUT_ELEMENT_DESC>();
			
			desc[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			desc[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };
			desc.shrink_to_fit();

			return std::make_shared<std::vector<D3D11_INPUT_ELEMENT_DESC>>();
		}
#endif // __cplusplus

		struct VertexInput
		{
			float4 Position SEMANTICS(POSTITION);
			float4 Color SEMANTICS(COLOR);
		};

		struct PixelInput
		{
			float4 Position SEMANTICS(SV_POSITION);
			float4 Color SEMANTICS(COLOR);
		};

#ifdef __cplusplus
	}
}
#endif