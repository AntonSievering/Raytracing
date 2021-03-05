/*
  O======================================================================================O
  |  Label.h, Label.cpp 																 |
  |  Version: 1.0																		 |
  |  Date:    01/12/2020																 |
  |  Author:  Anton Sievering															 |
  O======================================================================================O
*/

#pragma once
#include "Widget.h"
#include "Defines.h"


namespace Engine::GUI
{
	struct AutoScaledLabel : public Widget
	{
	public:
		Engine::Pixel col;

	private:
		std::string m_sText;
		float m_fSize;
		float m_fOffset;

	public:
		AutoScaledLabel() noexcept;
		AutoScaledLabel(const vf2d &pos, const vf2d &size, const std::string &sText, const Engine::Pixel &col = Engine::WHITE, const Alignment &align = Alignment::LEFT) noexcept;

	public:
		void setString(const std::string &sText, const Alignment &align = Alignment::LEFT) noexcept;
		virtual void draw(PixelEngine *engine) noexcept;
	};
}
