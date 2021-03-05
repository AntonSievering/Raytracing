#include "AutoScaledLabel.h"

namespace Engine::GUI
{
	AutoScaledLabel::AutoScaledLabel() noexcept : Widget()
	{
		m_sText = std::string();
		m_fSize = 0.0f;
	}
	
	AutoScaledLabel::AutoScaledLabel(const vf2d &pos, const vf2d &size, const std::string &sText, const Engine::Pixel &col, const Alignment &align) noexcept
		: Widget(Engine::vf2d(pos.x, pos.y + size.y), size)
	{
		this->col = col;
		m_sText = sText;
		setString(sText, align);
	}

	void AutoScaledLabel::setString(const std::string &sText, const Alignment &align) noexcept
	{
		vf2d vBaseStringSize = Engine::PixelEngine::GetStringSize(sText);
		m_fSize = size.y / vBaseStringSize.y;

		if (align == Alignment::CENTER)
			m_fOffset = 0.5f * (size.x - vBaseStringSize.x * m_fSize);
		else if (align == Alignment::RIGHT)
			m_fOffset = size.x - vBaseStringSize.x;
		else
			m_fOffset = 0.0f;
	}

	void AutoScaledLabel::draw(PixelEngine *engine) noexcept
	{
		engine->DrawStringHighRes({ pos.x + m_fOffset, pos.y }, m_fSize, m_sText, col);
	}
}
