Texture2D Texture : register(t0);
SamplerState ss : register(s0);


float3 CalcAmbient(float3 normal, float3 color) {

	float3 aD = float3(0.5, 0.5, 2.5);
	float3 aR = float3(1.0f, 0.5f, 0.5f);

	// Convert from [-1, 1] to [0, 1]
	float up = normal.y * 0.5 + 0.5;

	// Calculate the ambient value
	float3 ambient = aD + up * aR;
	//float3 ambient = aD + up * aR;

	// Apply the ambient value to the color
	return ambient * color;
}

float4 main(float4 position : SV_POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)  : SV_TARGET{


	//float3 diffuseColor = Texture.Sample(ss, texcoord).rgb;
	//diffuseColor *= diffuseColor;

	//float3 AmbientColor = CalcAmbient(normal, diffuseColor);

	//return float4(AmbientColor, 1.0);
	return Texture.Sample(ss, texcoord);

}

