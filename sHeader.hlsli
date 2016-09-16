cbuffer cbPerFrame : register(b0){
	matrix cameraScreenMatrix;

}

cbuffer cbPerMesh : register(b1){
	matrix worldMatrix;

}


Texture2D Texture : register(t0);
SamplerState ss : register(s0);