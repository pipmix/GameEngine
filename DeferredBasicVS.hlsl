cbuffer cbPerFrame : register(b2) {

	float4x4 cbWvp		: packoffset (c0);
	float4x4 cbWorld	: packoffset (c4);
}


struct VS_IN {

	float4 pos		: POSITION;
	float4 normal	: NORMAL;
	float2 uv		: TEXCOORD;
};


struct VS_OUT {

	float4 pos		: SV_POSITION;
	float2 uv		: TEXCOORD0;
	float3 normal	: TEXCOORD1;

};


VS_OUT main(VS_IN vs_in){

	VS_OUT vs_out;

	vs_out.pos = mul(vs_in.pos, cbWvp);
	vs_out.uv = vs_in.uv;
	vs_out.normal = mul(vs_in.normal, (float3x3)cbWorld);

	return vs_out;

}