#include "ImageBatch.h"

ImageBatch::ImageBatch()
{
}

void ImageBatch::UpdateBuffer(){

	std::vector<short> indices;



	D3D11_BUFFER_DESC indexBufferDesc = { 0 };



	indexBufferDesc.ByteWidth = sizeof(short) * 2048 * 4;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	//auto indexValues = CreateIndexValues();

	D3D11_SUBRESOURCE_DATA indexDataDesc = {0 };

	indexDataDesc.pSysMem = indices.data();


	//gDevice->CreateBuffer(&indexBufferDesc, &indexDataDesc, &indexBuffer);



	/*

	m_zd = 0.0f;
	VertexPU verts[4];

	if (m_centered) {

		verts[0] = { XMFLOAT3(-m_sprWH.x, m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) };
		verts[1] = { XMFLOAT3(m_sprWH.x, m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) };
		verts[2] = { XMFLOAT3(-m_sprWH.x, -m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) };
		verts[3] = { XMFLOAT3(m_sprWH.x, -m_sprWH.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) };
	}
	else {

		verts[0] = { XMFLOAT3(m_dim.x, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x, m_sourceRect.y) };
		verts[1] = { XMFLOAT3(m_dim.z, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) };
		verts[2] = { XMFLOAT3(m_dim.x, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) };
		verts[3] = { XMFLOAT3(m_dim.z, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) };

	}
	*/
	//m_numElements = ARRAYSIZE(verts);

	UINT numIndices= m_numImages * 4;
	VertexPU* verts = new VertexPU[numIndices];

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gContext->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, verts, sizeof(VertexPU) * numIndices);
	gContext->Unmap(m_vertexBuffer.Get(), 0);



	gContext->DrawIndexed(numIndices, 0, 0);


}

void ImageBatch::Draw(){

	// Set Resources
}


void ImageBatch::Add(const XMFLOAT4 & srcRect, const XMFLOAT4 & destRect, int texID){

	ImageStruct* temp = new ImageStruct();
	temp->textureID = texID;
	temp->depth = 0;
	temp->verts[0] = { XMFLOAT3(destRect.x, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Top left
	temp->verts[1] = { XMFLOAT3(destRect.x + srcRect.z, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Top Right
	temp->verts[2] = { XMFLOAT3(destRect.x, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Bottom left
	temp->verts[3] = { XMFLOAT3(destRect.x, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Bottom Right

	m_images.push_back(temp);

}

ResourceIDs ImageBatch::GetResourceIDs()
{
	return ResourceIDs();
}


void ImageBatch::Sort() {
	std::stable_sort(m_images.begin(), m_images.end(), TextureCompare);
}



bool TextureCompare(ImageStruct* a, ImageStruct* b) {
	return (a->depth > b->depth);
}
bool DepthCompare(ImageStruct* a, ImageStruct* b) {
	return (a->textureID < b->textureID);
}