struct VertexInput
{
	float4 Position : POSITION;
	float4 Color : COLOR;
};

struct PixelInput
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
};

PixelInput main(VertexInput input)
{
	PixelInput output;
	
	output.Position = input.Position;
	output.Color = input.Color;
	
	return output;
}