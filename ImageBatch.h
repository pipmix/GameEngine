#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include <vector>
#include <algorithm>


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;

class ImageStruct {
public:

	ImageStruct();
	ImageStruct(const XMFLOAT4 & srcRect, const XMFLOAT4 & destRect, int texID);


	VertexPU m_verts[4];
	int m_textureID;
	float m_depth;
	
};


struct ImageData {

	XMFLOAT4	sourceRect;
	XMFLOAT4	destRect;
	int			texId;


};

static bool TextureCompare(ImageStruct* a, ImageStruct* b);
static bool DepthCompare(ImageStruct* a, ImageStruct* b);

struct BatchQueue {
	
	int textureID;
	int numVerts;
	int offset;
	BatchQueue(int t, int n, int o) :textureID(t), numVerts(n), offset(o) {} ;
};

class ImageBatch {
public:

	ImageBatch();

	void UpdateBuffer();
	void Draw();
	void Sort();


	void Add(const XMFLOAT4& srcRect, const XMFLOAT4& destRect, int texID);
	void Finish();

	ResourceIDs GetResourceIDs();

	ResourceIDs	m_rIds;


	void CreateBatches();
private:

	ComPtr<ID3D11Buffer>		m_vertexBuffer;
	ComPtr<ID3D11Buffer>		m_indexBuffer;

	UINT m_numImages = 0;

	size_t m_curVBufferIndex;
	int m_curTex;


	std::vector<ImageStruct> m_images;
	std::vector<ImageStruct*> m_imagesP;
	std::vector<BatchQueue> m_batchQueues;
};