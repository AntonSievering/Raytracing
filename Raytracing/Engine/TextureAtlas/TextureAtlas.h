#pragma once

#include "../vec2d.h"
#include "../Sprite.h"

namespace Engine
{
	class TextureAtlas
	{
		using uint = uint32_t;

	private:
		Sprite *sprite;
		uint nSlots;
		vu2d textureSize;

	public:
		TextureAtlas();
		TextureAtlas(const vu2d &textureSize, const uint &nSlots);
		~TextureAtlas();

	public:
		void assign(const uint &slotId, Sprite *texture);
		void finish();

		void bind();

		Sprite *getSprite() const;
		vf2d getTextureCoordinate(const uint &slotId) const;
	};
}
