/*
  O======================================================================================O
  |  Button.h, Button.cpp																 |
  |  Version: 1.0																		 |
  |  Date:    01/12/2020																 |
  |  Author:  Anton Sievering															 |
  O======================================================================================O
*/

#pragma once
#include "../Engine.h"
#include "Label.h"


namespace Engine::GUI
{
	struct Button : public Widget
	{
	private:
		Sprite *m_normal, *m_pressed;
		Label m_text;

	public:
		Button()                                                                                                               noexcept;
		Button(const vf2d &pos, const vf2d &size, const std::string &sText, const Pixel &col, Sprite *normal, Sprite *pressed) noexcept;
	
	public:
		bool isOver(const vf2d &vMouse)                         noexcept;
		bool isPressed(PixelEngine *engine) noexcept;

		void setText(const std::string &sText);

	public:
		virtual void update(const float &fElapsedTime) noexcept override;
		virtual void draw(PixelEngine *engine)         noexcept override;
	};
}
