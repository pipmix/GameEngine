#include "HeaderVS.hlsli"



struct VS_IN {
	float4 pos : POSITION;
	float2 uv : TEXCOORD;
};



struct VS_OUT {
	float4 pos : SV_POSITION ;
	float2 uv : TEXCOORD;
};



VS_OUT main(VS_IN vs_in) {

	VS_OUT vs_out;

	vs_out = vs_in;

	return vs_out;
}