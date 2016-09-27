#include "Model.h"

Model::Model() {

	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_position = { 0.0f, 0.0f, 0.0f };
}

void Model::AssignResources(UINT texID, UINT vsID, UINT psID) {

	m_rIds.m_textureID = texID;
	m_rIds.m_vsID = vsID;
	m_rIds.m_psID = psID;

}

void Model::MoveBy(XMFLOAT3 moveBy){
	m_position.x += moveBy.x;
	m_position.y += moveBy.y;
	m_position.z += moveBy.z;
}

void Model::MoveTo(XMFLOAT3 moveTo){
	m_position.x = moveTo.x;
	m_position.y = moveTo.y;
	m_position.z = moveTo.z;

}


void Model::SetResources() {

	gDat.SetResources(m_rIds);



	UINT stride = sizeof(VertexPNU); // make automatic
	UINT offset = 0;

	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	gContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);




}

void Model::Draw() {



	SetResources();

	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->DrawIndexed(indexCount, 0 , 0);

}

void Model::Update() {


}


void Model::LoadMesh(wstring fN) {

	wstring completePathAndName = CV_baseDir + CV_meshDir + fN + CV_meshFileType;

	ifstream file(completePathAndName);
	string materialName, textureName;

	if (file) {

		file >> materialName >> textureName >> numOfIndices >> numOfVertices;

		unsigned short * indices = new unsigned short[numOfIndices];
		for (int i = 0; i < numOfIndices; i++) file >> indices[i];

		indexCount = numOfIndices;



		VertexPNU* vertices = new VertexPNU[numOfVertices];

		for (int i = 0; i < numOfVertices; i++) {
			file >> vertices[i].position.x
				>> vertices[i].position.y
				>> vertices[i].position.z
				>> vertices[i].normal.x
				>> vertices[i].normal.y
				>> vertices[i].normal.z
				>> vertices[i].texCoord.x
				>> vertices[i].texCoord.y;
		}
		file.close();

		D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;

		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPNU)*numOfVertices, D3D11_BIND_VERTEX_BUFFER);

		


		D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
		indexBufferData.pSysMem = indices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned short)*numOfIndices, D3D11_BIND_INDEX_BUFFER);

		gDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);
		gDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_indexBuffer);

		delete[] vertices;
		delete[] indices;
	}
	else Error(L"Mesh Load Error", completePathAndName.c_str());

}