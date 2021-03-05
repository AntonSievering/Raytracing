/*
  O======================================================================================O
  |  Panel.h, Panel.cpp 												                 |
  |  Version: 1.0																		 |
  |  Date:    01/12/2020																 |
  |  Author:  Anton Sievering															 |
  O======================================================================================O
*/

#pragma once
#include "Widget.h"


namespace Engine::GUI
{
	struct BasePanel : public Widget
	{
	public:
		BasePanel() noexcept;
		BasePanel(const vf2d &pos, const vf2d &size) noexcept;
	};

	struct Panel : public BasePanel
	{
	private:
		Pixel m_col;

	public:
		Panel() noexcept;
		explicit Panel(const Pixel &col) noexcept;
		Panel(const vf2d &pos, const vf2d &size, const Pixel &col) noexcept;

	public:
		virtual void draw(PixelEngine *engine) noexcept override;
	};
}
