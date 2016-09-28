#include "PS_Func.hlsli"

float4 main(float4 position :SV_POSITION, float2 uv : TEXCOORD0, float3 normal : TEXCOORD1 ) : SV_TARGET
{




	// Sample the texture and convert to linear space
	float3 DiffuseColor = Texture.Sample(ss, uv).rgb;
	DiffuseColor *= DiffuseColor;

	// Calculate the ambient color
	float3 AmbientColor = CalcAmbient(normal, DiffuseColor);

	// Return the ambient color
	return float4(AmbientColor, 1.0);




}

