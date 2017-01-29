Texture2D diffuseTexture : register(t0);
SamplerState linearSampler : register(s0);



cbuffer cbPerObjectPS : register (b0) {
	float cbSpecExp;
	float cbSpecInt;
}

struct PS_IN {

	float4 pos		: SV_POSITION;
	float2 uv		: TEXCOORD0;
	float3 normal	: TEXCOORD1;

};

struct PS_OUT {
	float4 color	: SV_TARGET0;
	float4 normal	: SV_TARGET1;
	float4 spec		: SV_TARGET2;
};




static const float2 g_SpecPowerRange = { 10.0, 250.0 };

PS_OUT main(PS_IN ps_in){
	PS_OUT ps_out;

	float3 diffuse = diffuseTexture.Sample(linearSampler, ps_in.uv);
	diffuse *= diffuse;


	ps_out.color = float4(diffuse.rgb, cbSpecInt);

	float4 n = float4(ps_in.normal * 0.5 + 0.5, 0.0);
	ps_out.normal = normalize(n);

	float specExpNorm = max(0.0001, (cbSpecExp - 10.0) / 250.0);
	ps_out.spec = float4(specExpNorm, 0.0, 0.0, 0.0);

	return ps_out;
}
