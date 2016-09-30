Texture2D Texture : register(t0);
SamplerState ss : register(s0);




float4 main(float4 position : SV_POSITION, float4 normal : COLOR, float2 texcoord : TEXCOORD)  : SV_TARGET{



	return Texture.Sample(ss, texcoord);

}

