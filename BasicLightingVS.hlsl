//#pragma pack_matrix( row_major )

#include "HeaderVS.hlsli"

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

	//float4 posWorld = mul(float4(position, 1), worldMatrix);

	//vs_out.position = mul(mul(posWorld, cameraMatrix), screenMatrix);

	matrix final; 


	//final = mul(screenMatrix, cameraMatrix);
	//final = mul(mul(screenMatrix, cameraMatrix), worldMatrix);

	
	//vs_out.position = mul(mul(mul(position, worldMatrix), cameraMatrix), screenMatrix);

	//float4x4 finalMatrix = mul(cameraScreenMatrix, worldMatrix);





	float4 col = float4(0.2, 0.2, 0.2, 1.0);
	float lgtVec = float4(1.0f, 1.0f, 1.0f, 0.0f);
	float lgtCol = float4(0.5, 0.5, 0.5, 1.0);



	

	float diffusebrightness = saturate(dot(lgtVec, normalize(mul(worldMatrix, normal))));    // calculate the diffuse brightness



	//vs_out.position = mul(finalMatrix, position);
	vs_out.position = mul(screenMatrix, mul(cameraMatrix, mul(worldMatrix, position)));
	vs_out.uv = texcoord;

	vs_out.color = col + (lgtCol * diffusebrightness);    // find the diffuse color and add


	return vs_out;
}