cbuffer perFrame : register(b0) {

	float4x4	cameraMatrix			: packoffset(c0);
	float4x4	screenMatrix			: packoffset(c4);
	float4x4	screenCameraMatrix		: packoffset(c8);

}


cbuffer perMesh : register(b1) {

	float4x4	worldMatrix						: packoffset(c0);
	float3x3	worldInverseTransposeMatrix		: packoffset(c4);

}

cbuffer skinningBuffer : register(b2) {

	float4x3	joints[64]							: packoffset(c0);
}


cbuffer lightingBuffers : register(b3) {

	float4 diffuseColor             : packoffset(c0);

};

struct VS_IN {
	float4 pos : SV_Position;
	float3 norm   : NORMAL;
	float2 uv : TEXCOORD0;
	uint4  blendIndices  : BLENDINDICES0; //BONEINDICES
	float4 blendWeights  : BLENDWEIGHT0; //WEIGHTS
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 norm	: NORMAL;
	float2 uv		: TEXCOORD0;


};







VS_OUT main(VS_IN vs_in) {

	VS_OUT vs_out;

	float4x3 skin = 0;

	skin += joints[vs_in.blendIndices[0]] * vs_in.blendWeights[0];
	skin += joints[vs_in.blendIndices[1]] * vs_in.blendWeights[1];
	skin += joints[vs_in.blendIndices[2]] * vs_in.blendWeights[2];
	skin += joints[vs_in.blendIndices[3]] * vs_in.blendWeights[3];

	vs_out.pos.xyz = mul(vs_in.pos, skin);
	vs_out.pos.w = 0;


	float3 normal = mul(vs_in.norm, (float3x3)skin);

	vs_out.norm = float4(normal, 0);//temp

	vs_out.uv = vs_in.uv;


	return vs_out;
}

