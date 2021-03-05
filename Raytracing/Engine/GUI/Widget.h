/*
  O======================================================================================O
  |  Widget.h, Widget.cpp															 	 |
  |  Widget is the base class for every user interface element. It has no functionality  |
  |  despite the possiblity to override it.												 |
  |																						 |
  |  Version: 1.0																		 |
  |  Date:    01/12/2020																 |
  |  Author:  Anton Sievering															 |
  O======================================================================================O
*/

#pragma once
#include "../Engine.h"
#include "../2DCollision/collision2d.h"


namespace Engine::GUI
{
	struct Widget
	{
	public:
		vf2d pos, size;
		bool bVisible = true;

	public:
		Widget() noexcept;
		Widget(const vf2d &pos, const vf2d &size) noexcept;

	public:
		virtual void update(const float &fElapsedTime) noexcept;
		virtual void draw(PixelEngine *engine) noexcept = 0;

	public:
		void hide() noexcept;
		void show() noexcept;
	};
}