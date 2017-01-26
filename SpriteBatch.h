#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include <vector>
#include <algorithm>


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;


struct SpriteInfo{
	XMFLOAT4	sourceRect;
	XMFLOAT4	destRect;
	int			texId;
};

class SpriteBatch {
public:

			SpriteBatch();
	void	Add(XMFLOAT4 srcRect, XMFLOAT4 destRect, int texId);
	void	Finish();
	void	Draw();

	void PrepareForRendering();
	void FlushBatch();
	void SortSprites();

private:

	int m_numSprites = 0;

	SpriteInfo m_sprites [256];

	std::vector<SpriteInfo const*> m_SortedSprites;
};