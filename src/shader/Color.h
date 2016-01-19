#pragma once

#if defined(__cplusplus)
#define SEMANTICS(semantic)
#else
#define SEMANTICS(semantic) : semantic
#endif

#ifdef __cplusplus
#include <DirectXMath.h>

using float4 = DirectX::XMFLOAT4;

namespace ColorShader
{
#endif // __cplusplus

	struct VertexInput
	{
		float4 Position SEMANTICS(POSTITION);
		float4 Color SEMANTICS(COLOR); 
	};

	struct PixelInput
	{
		float4 Position SEMANTICS(POSITION);
		float4 Color SEMANTICS(COLOR);
	};

#ifdef __cplusplus
}
#endif