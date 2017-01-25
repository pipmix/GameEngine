#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include <vector>
#include <algorithm>


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;

struct ImageStruct {
	VertexPU verts[4];
	int textureID;
	float depth;
};


struct ImageData {

	XMFLOAT4	sourceRect;
	XMFLOAT4	destRect;
	int			texId;


};

static bool TextureCompare(ImageStruct* a, ImageStruct* b);
static bool DepthCompare(ImageStruct* a, ImageStruct* b);

class ImageBatch {
public:

	ImageBatch();

	void UpdateBuffer();
	void Draw();
	void Sort();


	void Add(const XMFLOAT4& srcRect, const XMFLOAT4& destRect, int texID);

	ResourceIDs GetResourceIDs();

	ResourceIDs	m_rIds;



private:

	ComPtr<ID3D11Buffer>		m_vertexBuffer;
	ComPtr<ID3D11Buffer>		m_indexBuffer;

	UINT m_numImages = 0;

	size_t m_curVBufferIndex;

	std::vector<ImageStruct*> m_images;
};