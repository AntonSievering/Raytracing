#pragma once
#include "Widget.h"
#include "Defines.h"

namespace Engine::GUI
{
	class Label : public Widget
	{
	private:
		Engine::Pixel col;
		std::string sText;
		float fTextSize;
		Alignment align;

	public:
		Label() noexcept;
		Label(const vf2d &pos, const vf2d &size, const std::string &sText, const Engine::Pixel &col, const float &fTextSize, const Alignment &align = Alignment::LEFT) noexcept;

	public:
		void setString(const std::string &sText) noexcept;
		void setAlignment(const Alignment &alignment) noexcept;
		void draw(Engine::PixelEngine *engine) noexcept;
	};
}
