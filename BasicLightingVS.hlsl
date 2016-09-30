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


struct VS_OUT {
	float4 position : SV_POSITION;
	float4 color	: COLOR;
	float2 uv		: TEXCOORD;

};


VS_OUT main(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD) {


	VS_OUT vs_out;

	float4x4 finalMatrix = mul(cameraScreenMatrix, worldMatrix);

	float4 col = float4(0.2, 0.2, 0.2, 1.0);
	float lgtVec = float4(1.0f, 1.0f, 1.0f, 0.0f);
	float lgtCol = float4(0.5, 0.5, 0.5, 1.0);


	float4x4 lightMatix = mul(cameraMatrix, worldMatrix);
	float4 norm = normalize(mul(worldMatrix, normal));

	float diffusebrightness = saturate(dot(norm, lgtVec));    // calculate the diffuse brightness



	vs_out.position = mul(finalMatrix, position);

	vs_out.uv = texcoord;

	vs_out.color = col;
	vs_out.color += lgtCol * diffusebrightness;    // find the diffuse color and add


	return vs_out;
}