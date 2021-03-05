/*
  O======================================================================================O
  |  UserInterface.h, UserInterface.cpp 												 |
  |  Version: 1.0																		 |
  |  Date:    01/12/2020																 |
  |  Author:  Anton Sievering															 |
  O======================================================================================O
*/

#pragma once
#include "Label.h"
#include "Button.h"
#include "Picture.h"
#include "AutoScaledLabel.h"
#include <vector>


namespace Engine::GUI
{
	struct UserInterface : public Widget
	{
	private:
		std::vector<Widget *> m_vWidgets;
		AutoScaledLabel       m_title;
		Button                m_closeButton;
		bool                  m_bVisible;
		BasePanel            *m_background;

	public:
		UserInterface() noexcept;
		UserInterface(const vf2d &posOffset, const vf2d &size, BasePanel *background, const Pixel &textColor = WHITE) noexcept;

	public:
		void AddWidget(Widget *widget) noexcept;

		void show() noexcept;
		void hide() noexcept;
		bool isShown() const noexcept;

	public:
		virtual void update(const float &fElapsedTime) noexcept;
		virtual void draw(PixelEngine *engine) noexcept override;
	};
}
