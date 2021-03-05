#include "Panel.h"

namespace Engine::GUI
{
	BasePanel::BasePanel() noexcept : Widget()
	{
	}
	
	BasePanel::BasePanel(const vf2d &pos, const vf2d &size) noexcept : Widget(pos, size)
	{
	}


	Panel::Panel() noexcept
	{
		m_col = BLANK;
	}

	Panel::Panel(const Pixel &col) noexcept
	{
		m_col = col;
	}

	Panel::Panel(const vf2d &pos, const vf2d &size, const Pixel &col) noexcept : BasePanel(pos, size)
	{
		m_col = col;
	}

	void Panel::draw(PixelEngine *engine) noexcept
	{
		engine->DrawRectangle(pos, size, m_col);
	}
}
