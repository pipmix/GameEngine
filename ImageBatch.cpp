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



	for (int i = 0; i < m_batchQueues.size(); i++){
		// set texture

		//draw batchs[i] render offset/ numverts 
	}
}


void ImageBatch::Add(const XMFLOAT4 & srcRect, const XMFLOAT4 & destRect, int texID){

	if (m_numImages == 0) {

		m_images.clear();
		m_batchQueues.clear();
	}


	m_images.emplace_back(srcRect, destRect, texID);
	m_numImages++;
}

void ImageBatch::Finish(){
	m_imagesP.resize(m_images.size());
	for (int i = 0; i < m_images.size(); i++){
		m_imagesP[i] = &m_images[i];
	}
	Sort();
	CreateBatches();
}

ResourceIDs ImageBatch::GetResourceIDs()
{
	return ResourceIDs();
}

void ImageBatch::CreateBatches()
{
	m_curTex = -1;
	std::vector <VertexPU> v;
	v.resize(m_imagesP.size() * 6);
	if (m_imagesP.empty())return;

	//BatchQueue temp{ 0, 6, m_images[0]->textureID };

	//m_batchQueues.push_back(temp);
	int curVert = 0;
	int curOffset = 0;

	m_batchQueues.emplace_back(0, 6, m_imagesP[0]->m_textureID);
	v[curVert + 0] = m_imagesP[0]->m_verts[0];
	v[curVert + 1] = m_imagesP[0]->m_verts[1];
	v[curVert + 2] = m_imagesP[0]->m_verts[2];
	v[curVert + 3] = m_imagesP[0]->m_verts[1];
	v[curVert + 4] = m_imagesP[0]->m_verts[3];
	v[curVert + 5] = m_imagesP[0]->m_verts[2];

	for (int i = 0; i < m_images.size(); i++) {

		if (m_curTex != m_imagesP[i]->m_textureID) {
			m_batchQueues.emplace_back(curOffset, 6, m_imagesP[i]->m_textureID);
			m_curTex = m_imagesP[i]->m_textureID;
		}
		else {
			m_batchQueues.back().numVerts += 6;
		}

		curVert = i * 6;
		v[curVert + 0] = m_imagesP[i]->m_verts[0];
		v[curVert + 1] = m_imagesP[i]->m_verts[1];
		v[curVert + 2] = m_imagesP[i]->m_verts[2];
		v[curVert + 3] = m_imagesP[i]->m_verts[1];
		v[curVert + 4] = m_imagesP[i]->m_verts[3];
		v[curVert + 5] = m_imagesP[i]->m_verts[2];
		curOffset += 6;

	}

}


void ImageBatch::Sort() {
	std::stable_sort(m_imagesP.begin(), m_imagesP.end(), TextureCompare);
}



bool TextureCompare(ImageStruct* a, ImageStruct* b) {
	return (a->m_depth > b->m_depth);
}
bool DepthCompare(ImageStruct* a, ImageStruct* b) {
	return (a->m_textureID < b->m_textureID);
}

ImageStruct::ImageStruct()
{
}

ImageStruct::ImageStruct(const XMFLOAT4 & srcRect, const XMFLOAT4 & destRect, int texID){


	m_textureID = texID;
	m_depth = 0;
	m_verts[0] = { XMFLOAT3(destRect.x, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Top left
	m_verts[1] = { XMFLOAT3(destRect.x + srcRect.z, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Top Right
	m_verts[2] = { XMFLOAT3(destRect.x, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Bottom left
	m_verts[3] = { XMFLOAT3(destRect.x, destRect.y + srcRect.w, 0.0f), XMFLOAT2(srcRect.x, srcRect.y + srcRect.w) }; // Bottom Right

}
