#include "Color.h"

float4 main(PixelInput input) : SV_TARGET
{
	return input.Color;
}