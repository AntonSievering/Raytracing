#include "Button.h"

namespace Engine::GUI
{
	Button::Button() noexcept : Widget()
	{
		m_normal = m_pressed = nullptr;
	}

	Button::Button(const vf2d &pos, const vf2d &size, const std::string &sText, const Pixel &col, Sprite *normal, Sprite *pressed) noexcept : Widget(pos, size)
	{
		m_normal = normal;
		m_pressed = pressed;
		m_text = Label(pos, size, sText, col, 2.0f, Alignment::CENTER);
	}

	bool Button::isOver(const vf2d &vMouse) noexcept
	{
		return bVisible && Collision2D::rect(pos, size).collide(vMouse);
	}

	bool Button::isPressed(PixelEngine *engine) noexcept
	{
		return isOver(engine->GetMouse()) && engine->GetKey(Engine::Key::MOUSE_LEFT).bReleased;
	}

	void Button::setText(const std::string &sText)
	{
		m_text.setString(sText);
	}

	void Button::update(const float &fElapsedTime) noexcept
	{
	}

	void Button::draw(PixelEngine *engine) noexcept
	{
		if (isOver(engine->GetMouse()))
			engine->DrawSprite(m_pressed, pos, size);
		else
			engine->DrawSprite(m_normal, pos, size);
		m_text.draw(engine);
	}
}