#include "Label.h"

namespace Engine::GUI
{
	Label::Label() noexcept
	{
		fTextSize = 0.0f;
		align = Alignment::LEFT;
	}
	
	Label::Label(const vf2d &pos, const vf2d &size, const std::string &sText, const Engine::Pixel &col, const float &fTextSize, const Alignment &align) noexcept
		: Widget(pos, size)
	{
		this->col = col;
		this->fTextSize = fTextSize;
		this->sText = sText;
		this->align = align;
	}
	
	void Label::setString(const std::string &sText) noexcept
	{
		this->sText = sText;
	}

	void Label::setAlignment(const Alignment &alignment) noexcept
	{
		align = alignment;
	}

	void Label::draw(Engine::PixelEngine *engine) noexcept
	{
		Engine::vf2d vPos = pos;
		Engine::vf2d vTextSize = engine->GetStringSize(sText) * fTextSize;

		// X-Alignment
		if (align == Alignment::CENTER)
			vPos.x += (size.x - vTextSize.x) * 0.5f;
		else if (align == Alignment::RIGHT)
			vPos.x += (size.x - vTextSize.x);

		// Y-Alignment
		vPos.y += (size.y + vTextSize.y) * 0.5f;

		engine->DrawStringLowRes(vPos, fTextSize, sText, col);
	}


}
