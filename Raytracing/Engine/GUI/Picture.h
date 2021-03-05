/*
  O======================================================================================O
  |  Picture.h, Picture.cpp 															 |
  |  Version: 1.0																		 |
  |  Date:    01/12/2020																 |
  |  Author:  Anton Sievering															 |
  O======================================================================================O
*/

#pragma once
#include "Panel.h"


namespace Engine::GUI
{
	struct Picture : public BasePanel
	{
	private:
		Sprite *m_sprite;

	public:
		Picture() noexcept;
		explicit Picture(Sprite *sprite) noexcept;
		Picture(const vf2d &pos, const vf2d &size, Sprite *sprite) noexcept;

	public:
		virtual void draw(PixelEngine *engine) noexcept override;
	};
}
