// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Widget.hpp"
#include "Manager.hpp"
#include "../../helpers/Util.hpp"

using namespace Gui;

Widget::Ptr Widget::create()
{
	Widget::Ptr widget = Widget::Ptr(new Widget());

	widget->m_widget = widget;

	return widget;
}

Widget::Ptr Widget::create(sf::Vector2i size)
{
	auto widget = create();
	widget->setSize(size);

	return widget;
}

Widget::Ptr Widget::create(sf::Vector2i size, sf::Vector2f position)
{
	auto widget = create();
	widget->setSize(size);
	widget->setPosition(position);

	return widget;
}

sf::Vector2f Widget::getPosition()
{
	return m_position;
}

sf::Vector2f Widget::getAbsolutePosition()
{
	if(m_parentWidget)
	{
		return (getPosition() + m_parentWidget->getPosition());
	}

	return getPosition();
}

void Widget::setPosition(sf::Vector2f position)
{
	m_position = position;
}

sf::Vector2i Widget::getSize()
{
	return m_size;
}

void Widget::setSize(sf::Vector2i size)
{
	m_size = size;
}

bool Widget::isEnabled()
{
	return m_enabled;
}

void Widget::toggleEnabled(bool enabled)
{
	m_enabled = enabled;
}

void Widget::handleRender(sf::RenderTarget& target, sf::RenderStates states)
{
	onRender(target, states);

	if(!m_childWidgets.empty())
	{
		for (auto it : m_childWidgets)
		{
			it->handleRender(target, states);
		}
	}
}

void Widget::handleMouseMotion(MouseInfoPtr mouse)
{
	if(!m_enabled)
	{
		return;
	}

	if(onMouseMotion(mouse))
	{
		if(!m_childWidgets.empty())
		{
			for (auto it : m_childWidgets)
			{
				if(collisionRectPoint(it->getAbsolutePosition(), sf::Vector2f(it->getSize()), sf::Vector2f(mouse->x, mouse->y)))
				{
					it->handleMouseMotion(mouse);

					break;
				}
			}
		}

		if(m_manager.lock()->m_widgetHover.expired())
		{
			m_manager.lock()->m_widgetHover = m_widget.lock();
		}
	}
}

void Widget::handleMouseDown(MouseInfoPtr mouse)
{
	if(!m_enabled)
	{
		return;
	}

	if(onMouseDown(mouse))
	{
		if(!m_childWidgets.empty())
		{
			for (auto it : m_childWidgets)
			{
				if(collisionRectPoint(it->getPosition(), sf::Vector2f(it->getSize()), sf::Vector2f(mouse->x, mouse->y)))
				{
					it->handleMouseDown(mouse);

					break;
				}
			}
		}

		if(m_manager.lock()->m_widgetFocused.expired())
		{
			m_manager.lock()->m_widgetFocused = m_widget.lock();
		}
	}
}

bool Widget::isMouseHover()
{
	return (m_manager.lock()->m_widgetHover.lock() == m_widget.lock());
}
