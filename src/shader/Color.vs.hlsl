#include "Color.h"

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

PixelInput main(VertexInput input)
{
	PixelInput output;

	input.Position.w = 1.0f;
	
	output.Position = mul(input.Position, worldMatrix);
	output.Position = mul(output.Position, viewMatrix);
	output.Position = mul(output.Position, projectionMatrix);

	output.Color = input.Color;
	
	return output;
}