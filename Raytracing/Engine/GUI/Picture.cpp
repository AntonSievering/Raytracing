#include "Picture.h"

namespace Engine::GUI
{
	Picture::Picture() noexcept : BasePanel()
	{
		m_sprite = nullptr;
	}

	Picture::Picture(Sprite *sprite) noexcept
	{
		m_sprite = sprite;
	}

	Picture::Picture(const vf2d &pos, const vf2d &size, Engine::Sprite *sprite) noexcept : BasePanel(pos, size)
	{
		m_sprite = sprite;
	}

	void Picture::draw(PixelEngine *engine) noexcept
	{
		engine->DrawSprite(m_sprite, pos, size);
	}
}
