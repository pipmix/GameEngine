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
	float2 texcoord : TEXCOORD;

};


VS_OUT main( float4 position : POSITION, float2 texcoord : TEXCOORD ) {


	VS_OUT vs_out;

	float4x4 finalMatrix = mul(cameraScreenMatrix, worldMatrix);

	vs_out.position = mul(finalMatrix, position);
	vs_out.texcoord = texcoord;



	return vs_out;
}
// last good vs_out.position = mul(worldMatrix, position);

