#include "TextureAtlas.h"

namespace Engine
{
	TextureAtlas::TextureAtlas()
	{
		sprite = nullptr;
		nSlots = 0;
	}

	TextureAtlas::TextureAtlas(const vu2d &textureSize, const uint &nSlots)
	{
		sprite = new Sprite(vu2d(textureSize.x * nSlots, textureSize.y), GL_LINEAR, GL_NEAREST);
		this->textureSize = textureSize;
		this->nSlots = nSlots;
	}

	TextureAtlas::~TextureAtlas()
	{
		delete sprite;
	}

	void TextureAtlas::assign(const uint &slotId, Sprite *texture)
	{
		if (slotId < nSlots)
		{
			uint offset = slotId * textureSize.x;

			for (uint y = 0; y < textureSize.y; y++)
				for (uint x = 0; x < textureSize.x; x++)
					sprite->SetPixel({ x + offset, y }, texture->GetPixel({ x, y }));
		}
	}

	void TextureAtlas::finish()
	{
		sprite->reupload();
	}

	void TextureAtlas::bind()
	{
		sprite->bind();
	}

	Sprite *TextureAtlas::getSprite() const
	{
		return sprite;
	}

	vf2d TextureAtlas::getTextureCoordinate(const uint &slotId) const
	{
		return { (float)slotId / (float)nSlots + 0.0002f, (float)(slotId + 1.0f) / (float)nSlots - 0.0002f };
	}
}
