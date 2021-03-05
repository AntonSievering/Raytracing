#include "UserInterface.h"

namespace Engine::GUI
{
	UserInterface::UserInterface() noexcept
	{
		m_bVisible = false;
		m_background = nullptr;
	}

	UserInterface::UserInterface(const vf2d &posOffset, const vf2d &size, BasePanel *background, const Pixel &textColor) noexcept : Widget(posOffset, size)
	{
		m_bVisible         = true;
		m_title            = AutoScaledLabel({ pos.x, pos.y + 0.9f * size.y }, { 0.9f * size.x, 0.1f * size.y }, "Title", textColor, Alignment::LEFT);
		m_closeButton      = Button({ pos.x + 0.9f * size.x, pos.y + 0.9f * size.y }, { 0.1f * size.x, 0.1f * size.y }, "X", textColor, nullptr, nullptr);
		m_background       = background;
		m_background->pos  = pos;
		m_background->size = size;
	}
	
	void UserInterface::AddWidget(Widget *widget) noexcept
	{
		m_vWidgets.push_back(widget);
		m_vWidgets.at(m_vWidgets.size() - 1)->pos += pos;
	}

	void UserInterface::show() noexcept
	{
		m_bVisible = true;
	}

	void UserInterface::hide() noexcept
	{
		m_bVisible = false;
	}

	bool UserInterface::isShown() const noexcept
	{
		return m_bVisible;
	}
	
	void UserInterface::update(const float &fElapsedTime) noexcept
	{
		for (Widget *widget : m_vWidgets)
			widget->update(fElapsedTime);
	}

	void UserInterface::draw(PixelEngine *engine) noexcept
	{
		if (m_closeButton.isPressed(engine))
			m_bVisible = false;

		if (m_bVisible)
		{
			// Draw UI
			m_background->draw(engine);
			m_title.draw(engine);
			m_closeButton.draw(engine);

			for (Widget *widget : m_vWidgets)
				widget->draw(engine);
		}
	}
}
