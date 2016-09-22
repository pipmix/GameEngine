
cbuffer cbPerFrame : register(b0) {
	matrix cameraScreenMatrix;

}

cbuffer cbPerMesh : register(b1) {
	matrix worldMatrix;

}



struct VS_OUT {
	float4 position :	SV_POSITION;
	float2 texcoord	:	TEXCOORD;

};

VS_OUT main( float4 position : POSITION, float2 texcoord : TEXCOORD ) {
	VS_OUT vs_out;

	vs_out.position = position;
	vs_out.texcoord = texcoord;
	return vs_out;
}


