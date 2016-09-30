cbuffer cbPerFrame : register(b0) {
	matrix cameraScreenMatrix;
	matrix cameraMatrix;
	matrix screenMatrix;

}

cbuffer cbPerMesh : register(b1) {
	matrix worldMatrix;

}

cbuffer cbPerResize : register(b2) {
	float4 screenDim;

}



struct VS_IN {

	float4 pos : POSITION;
	float2 texcoord : TEXCOORD;

};

struct VS_OUT {

	float4 pos : SV_POSITION;
	float2 texcoord: TEXCOORD;

};



VS_OUT main(VS_IN vs_in)
{


	VS_OUT vs_out;

	vs_out.pos = mul(cameraScreenMatrix, vs_in.pos);
	

	vs_out.texcoord = vs_in.texcoord;

	return vs_out;


}