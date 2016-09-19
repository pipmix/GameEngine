Texture2D Texture : register(t0);
SamplerState ss : register(s0);


float4 main(float4 position : SV_POSITION, float2 texcoord : TEXCOORD) : SV_TARGET{

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return Texture.Sample(ss, texcoord);
}