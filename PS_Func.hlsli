									/// Pixel Shaders Header ///
Texture2D Texture : register(t0);
SamplerState ss : register(s0);

cbuffer cbPS_amb	:	register(b0){
	float4 ambUp	:	packoffset(c0);
	float4 ambDown	:	packoffset(c1);
}

cbuffer cbPS_lights :	register(b1){
	float4 lights1	:	packoffset(c0);
	float4 lights2	:	packoffset(c1);
}

float3 CalcAmbient(float3 normal, float3 color){
	// Convert from [-1, 1] to [0, 1]
	float up = normal.y * 0.5 + 0.5;
	// Calculate the ambient value
	float3 Ambient = ambDown + up * ambUp;
	// Apply the ambient value to the color
	return Ambient * color;
}

