// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include "Widget.hpp"
#include "../../input/Input.hpp"

namespace Gui
{
class Manager : public sf::Drawable
{
	public:
		typedef std::shared_ptr<Manager> Ptr;
		typedef std::weak_ptr<Manager> WeakPtr;

		~Manager();

		static Manager::Ptr create(Input::Ptr input);
		void addWidget(Widget::Ptr widget);
		void addWidget(Widget::Ptr widget, Widget::Ptr container);
		void removeWidget(Widget::Ptr widget);

	protected:
		Manager(Input::Ptr input);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void onMouseMotion(MouseInfoPtr mouse);
		void onMouseDown(MouseInfoPtr mouse);
		void onMouseUp(MouseInfoPtr mouse);
		void onKeyDown(int keyCode);
		void onKeyUp(int keyCode);

		Manager::WeakPtr m_manager;
		Widget::List m_widgets;
		Widget::Ptr m_mainContainer;
		Widget::WeakPtr m_widgetFocused;
		Widget::WeakPtr m_widgetHover;

	friend class Widget;
};
}

#endif // GUI_MANAGER_HPP
