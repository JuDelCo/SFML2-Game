// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef GUI_WIDGET_HPP
#define GUI_WIDGET_HPP

#include <memory>
#include "../../input/Input.hpp"

namespace Gui
{
class Manager;
typedef std::weak_ptr<Manager> ManagerWeakPtr;

class Widget
{
	public:
		typedef std::shared_ptr<Widget> Ptr;
		typedef std::weak_ptr<Widget> WeakPtr;
		typedef std::vector<Widget::Ptr> List;

		~Widget() {}

		static Widget::Ptr create();
		static Widget::Ptr create(sf::Vector2i size);
		static Widget::Ptr create(sf::Vector2i size, sf::Vector2f position);
		sf::Vector2f getPosition();
		sf::Vector2f getAbsolutePosition();
		void setPosition(sf::Vector2f position);
		sf::Vector2i getSize();
		void setSize(sf::Vector2i size);
		bool isEnabled();
		void toggleEnabled(bool enabled);

	protected:
		Widget() {}

		virtual void onRender(sf::RenderTarget& target, sf::RenderStates states) {}
		virtual bool onMouseMotion(MouseInfoPtr mouse) { return true; }
		virtual bool onMouseDown(MouseInfoPtr mouse) { return true; }
		virtual void onMouseUp(MouseInfoPtr mouse) {}
		virtual void onKeyDown(int keyCode) {}
		virtual void onKeyUp(int keyCode) {}
		bool isMouseHover();

		Widget::WeakPtr m_widget;

	private:
		void handleRender(sf::RenderTarget& target, sf::RenderStates states);
		void handleMouseMotion(MouseInfoPtr mouse);
		void handleMouseDown(MouseInfoPtr mouse);

		bool m_enabled = true;
		ManagerWeakPtr m_manager;
		Widget::Ptr m_parentWidget;
		Widget::List m_childWidgets;
		sf::Vector2f m_position = sf::Vector2f(0,0);
		sf::Vector2i m_size = sf::Vector2i(0,0);

	friend class Manager;
};
}

#endif // GUI_WIDGET_HPP
