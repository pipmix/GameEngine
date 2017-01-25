#include "HeaderVS.hlsli"

struct VS_IN {

	float4 pos : POSITION;
	float4 normal : NORMAL;
	float2 uv : TEXCOORD;
	uint4 SkinIndices : BLENDINDICES;
	float4 SkinWeights : BLENDWEIGHT;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};


VS_OUT main(VS_IN vs_in) {
	VS_OUT vs_out;
	vs_out.pos = vs_in.pos;
	vs_out.uv = vs_in.uv;
	return vs_out;
}
