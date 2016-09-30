cbuffer cbPerFrame : register(b0) {
	matrix cameraScreenMatrix;

}

cbuffer cbPerMesh : register(b1) {
	matrix worldMatrix;

}

cbuffer cbPerResize : register(b2) {
	float4 screenDim;

}



struct VS_OUT {
	float4 position : SV_POSITION;
	float4 normal	: COLOR;
	float2 uv		: TEXCOORD;

};


VS_OUT main(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD) {


	VS_OUT vs_out;

	float4x4 finalMatrix = mul(cameraScreenMatrix, worldMatrix);

	vs_out.position = mul(finalMatrix, position);
	vs_out.normal = mul(finalMatrix, normal);
	vs_out.uv = texcoord;


	return vs_out;
}