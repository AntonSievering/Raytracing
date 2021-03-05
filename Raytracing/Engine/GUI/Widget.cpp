#include "Widget.h"

namespace Engine::GUI
{
	Widget::Widget() noexcept
	{
	}
	
	Widget::Widget(const vf2d &pos, const vf2d &size) noexcept
	{
		this->pos  = pos;
		this->size = size;
	}
	
	void Widget::update(const float &fElapsedTime) noexcept
	{
	}
	
	void Widget::hide() noexcept
	{
		bVisible = false;
	}
	
	void Widget::show() noexcept
	{
		bVisible = true;
	}
}
