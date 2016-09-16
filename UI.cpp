#include "UI.h"

UI::UI()
{
}

void UI::Initialize(){

	//CD3D11_TEXTURE2D_DESC texDes()


	// Create vertex buffer


	D3D11_BUFFER_DESC vbd = {0};

	vbd.Usage = D3D11_USAGE_DYNAMIC;
	//vbd.ByteWidth = sizeof(VertexPositionColorTexture) * MaxBatchSize * VerticesPerSprite;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//gDevice->CreateBuffer(&vbd, nullptr, &m_vertexBuffer);
	


}
