#include "Shader.h"

// Vertex Shader
VertexShader::VertexShader() {

}

void VertexShader::Load(std::wstring fn, VertexType vt) {


	std::wstring fileName = L"C:/Shaders/" + fn + L".cso";

	UINT8*	vsData;
	UINT	vsDataLength;

	ReadDataFromFile(fileName.c_str(), &vsData, &vsDataLength);

	gDevice->CreateVertexShader(vsData, vsDataLength, nullptr, &vertexShader);

	switch (vt) {

	case VT_P:
		gDevice->CreateInputLayout(VertexP_Layout, ARRAYSIZE(VertexP_Layout), vsData, vsDataLength, &inputLayout);
		break;
	case VT_PU:
		gDevice->CreateInputLayout(VertexPU_Layout, ARRAYSIZE(VertexPU_Layout), vsData, vsDataLength, &inputLayout);
		break;
	case VT_PNU:

		break;
	default:
		break;
	};



};

void VertexShader::Set() {

	gContext->VSSetShader(vertexShader.Get(), 0, 0);
	gContext->IASetInputLayout(inputLayout.Get());
	
}


// Pixel Shader
PixelShader::PixelShader() {

}


void PixelShader::Load(std::wstring fn) {

	std::wstring fileName = L"C:/Shaders/" + fn + L".cso";

	UINT8*	psData;
	UINT	psDataLength;

	ReadDataFromFile(fileName.c_str(), &psData, &psDataLength);

	gDevice->CreatePixelShader(psData, psDataLength, nullptr, &pixelShader);

}

void PixelShader::Set() {

	gContext->PSSetShader(pixelShader.Get(), 0, 0);

}
