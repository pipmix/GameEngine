#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
}

void SpriteBatch::Add(XMFLOAT4 srcRect, XMFLOAT4 destRect, int texId){
	SpriteInfo* spr = &m_sprites[m_numSprites];

	spr->sourceRect = srcRect;
	spr->destRect = destRect;
	spr->texId = texId;

	m_numSprites++;

}

void SpriteBatch::Finish(){

	PrepareForRendering();
	FlushBatch();
}



void SpriteBatch::PrepareForRendering()
{
}

void SpriteBatch::FlushBatch()
{
	SortSprites();
}

void SpriteBatch::SortSprites(){


	std::sort(m_SortedSprites.begin(), m_SortedSprites.begin() + m_numSprites, [](SpriteInfo const* x, SpriteInfo const* y) -> bool
	{
		return x->texId < y->texId;
	});

}





void SpriteBatch::Draw() {


}