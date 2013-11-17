// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Manager.hpp"
#include "../../helpers/Util.hpp"

using namespace Gui;

Manager::Ptr Manager::create(Input::Ptr input)
{
	Manager::Ptr manager = Manager::Ptr(new Manager(input));

	manager->m_manager = manager;

	// Hack to make sure MainContainer capture all mouse events
	manager->m_mainContainer = Widget::create(sf::Vector2i(1000000,1000000), sf::Vector2f(0, 0));
	manager->m_mainContainer->m_manager = manager->m_manager.lock();
	manager->m_widgets.push_back(Widget::Ptr(manager->m_mainContainer));

	return manager;
}

Manager::~Manager()
{
	removeWidget(m_mainContainer);
}

void Manager::addWidget(Widget::Ptr widget)
{
	addWidget(widget, m_mainContainer);
}

void Manager::addWidget(Widget::Ptr widget, Widget::Ptr container)
{
	if(!widget)
	{
		return;
	}

	if(widget->m_parentWidget)
	{
		return;
	}

	auto it = std::find(m_widgets.begin(), m_widgets.end(), widget);

	if(it != m_widgets.end())
	{
		return;
	}

	it = std::find(container->m_childWidgets.begin(), container->m_childWidgets.end(), widget);

	if(it != container->m_childWidgets.end())
	{
		return;
	}

	it = std::find(m_widgets.begin(), m_widgets.end(), container);

	if(it == m_widgets.end())
	{
		return;
	}

	widget->m_manager = m_manager.lock();
	widget->m_parentWidget = container;
	container->m_childWidgets.push_back(Widget::Ptr(widget));

	m_widgets.push_back(Widget::Ptr(widget));
}

void Manager::removeWidget(Widget::Ptr widget)
{
	for (auto it = widget->m_childWidgets.begin(); it != widget->m_childWidgets.end();)
	{
		auto childWidget = Widget::Ptr(*it);

		it = widget->m_childWidgets.erase(it);

		removeWidget(childWidget);
	}

	widget->m_childWidgets.clear();

	if(widget->m_parentWidget)
	{
		auto it = std::find(widget->m_parentWidget->m_childWidgets.begin(), widget->m_parentWidget->m_childWidgets.end(), widget);

		if(it != widget->m_parentWidget->m_childWidgets.end())
		{
			widget->m_parentWidget->m_childWidgets.erase(it);
		}

		widget->m_parentWidget.reset();
	}

	auto it = std::find(m_widgets.begin(), m_widgets.end(), widget);

	if(it != m_widgets.end())
	{
		m_widgets.erase(it);
	}
}

Manager::Manager(Input::Ptr input)
{
	input->EventMouseMotion.connect(Event::CreateCallBack(this, &Manager::onMouseMotion));
	input->EventMouseDown.connect(Event::CreateCallBack(this, &Manager::onMouseDown));
	input->EventMouseUp.connect(Event::CreateCallBack(this, &Manager::onMouseUp));
	input->EventKeyDown.connect(Event::CreateCallBack(this, &Manager::onKeyDown));
	input->EventKeyUp.connect(Event::CreateCallBack(this, &Manager::onKeyUp));
}

void Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_mainContainer->handleRender(target, states);
}

void Manager::onMouseMotion(MouseInfoPtr mouse)
{
	m_widgetHover.reset();

	m_mainContainer->handleMouseMotion(mouse);
}

void Manager::onMouseDown(MouseInfoPtr mouse)
{
	m_widgetFocused.reset();

	m_mainContainer->handleMouseDown(mouse);
}

void Manager::onMouseUp(MouseInfoPtr mouse)
{
	if(!m_widgetFocused.expired())
	{
		auto it = std::find(m_widgets.begin(), m_widgets.end(), m_widgetFocused.lock());

		if(it != m_widgets.end())
		{
			if((*it)->isEnabled())
			{
				(*it)->onMouseUp(mouse);
			}
		}
	}
}

void Manager::onKeyDown(int keyCode)
{
	if(!m_widgetFocused.expired())
	{
		auto it = std::find(m_widgets.begin(), m_widgets.end(), m_widgetFocused.lock());

		if(it != m_widgets.end())
		{
			if((*it)->isEnabled())
			{
				(*it)->onKeyDown(keyCode);
			}
		}
	}
}

void Manager::onKeyUp(int keyCode)
{
	if(!m_widgetFocused.expired())
	{
		auto it = std::find(m_widgets.begin(), m_widgets.end(), m_widgetFocused.lock());

		if(it != m_widgets.end())
		{
			if((*it)->isEnabled())
			{
				(*it)->onKeyUp(keyCode);
			}
		}
	}
}
