
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
	float4 position :	SV_POSITION;
	float2 texcoord	:	TEXCOORD;

};

VS_OUT main( float4 position : POSITION, float2 texcoord : TEXCOORD ) {
	VS_OUT vs_out;

	vs_out.position = position;
	vs_out.texcoord = texcoord;

	//vs_out.position = float4(2.0 * position.x / screenDim.x - 1.0, 1.0 - 2.0 * position.y / screenDim.y, 0, 1);
	
	return vs_out;
}


// vs_out.position = float4(2.0 * vs_out.position.x / screenDim.x - 1.0, 1.0 - 2.0 * vs_out.position.y / screenDim.y, 0, 1);