cbuffer cbPerFrame : register(b0) {
	matrix cameraScreenMatrix;

}

cbuffer cbPerMesh : register(b1) {
	matrix worldMatrix;

}


struct VS_OUT {
	float4 position : SV_POSITION;
	float3 normal	: NORMAL;
	float2 texcoord : TEXCOORD;

};


VS_OUT main(float4 position : POSITION, float3 normal : NORMAL, float2 texcoord : TEXCOORD) {


	VS_OUT vs_out;

	float4x4 finalMatrix = mul(cameraScreenMatrix, worldMatrix);

	vs_out.position = mul(finalMatrix, position);
	vs_out.normal = normal;
	vs_out.texcoord = texcoord;

	return vs_out;
}