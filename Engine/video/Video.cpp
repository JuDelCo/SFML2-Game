#include "Video.hpp"
#include "../Defines.hpp"


Video::Video()
{
	m_resolution = sf::Vector2u(640, 480);
	m_title = "Demo";
	m_fpsLimit = 60.0;

	m_window = RenderWindowPtr(new sf::RenderWindow());
}


Video::~Video()
{
	endWindow();
}


bool Video::init()
{
	if(!m_window->isOpen())
	{
		initWindow();

		m_window->setKeyRepeatEnabled(false);
		m_window->clear();

		if(m_window->isOpen())
		{
			return true;
		}
	}

	return false;
}


void Video::initWindow()
{
	m_window->create(sf::VideoMode(m_resolution.x, m_resolution.y), m_title, sf::Style::Titlebar | sf::Style::Close);

	m_window->setFramerateLimit(m_fpsLimit);
	m_window->setVerticalSyncEnabled(true);

	if (!m_window->isOpen())
	{
		exit(ERROR_INIT);
	}
}


void Video::endWindow()
{
	if(m_window->isOpen())
	{
		m_window->close();
	}
}


void Video::swapBuffers()
{
	m_window->display();
}


sf::Vector2u Video::getSize()
{
	return m_window->getSize();
}


RenderWindowPtr Video::getWindow()
{
	return m_window;
}


sf::Vector2i Video::getCameraPosition()
{
	return m_cameraPosition;
}


float Video::getFpsLimit()
{
	return m_fpsLimit;
}


void Video::setFpsLimit(float fpsLimit)
{
	if(fpsLimit > 0)
	{
		m_fpsLimit = fpsLimit;
	}
}


void Video::changeTitle(std::string title)
{
	m_title = title;

	if(m_window->isOpen())
	{
		m_window->setTitle(m_title);
	}
}


void Video::changeResolution(sf::Vector2u resolution)
{
	m_resolution = resolution;

	if(m_window->isOpen())
	{
		initWindow();
	}
}


void Video::setCameraPosition(sf::Vector2i position)
{
	m_cameraPosition = position;
}


void Video::moveCameraPosition(sf::Vector2i offset)
{
	m_cameraPosition += offset;
}


void Video::viewReset(sf::FloatRect rect)
{
	sf::View view = m_window->getView();

	view.reset(rect);

	m_window->setView(view);
}


void Video::viewResetToCamera()
{
	viewReset(sf::FloatRect(getCameraPosition().x, getCameraPosition().y, getSize().x, getSize().y));
}


void Video::clear(sf::Color color)
{
	m_window->clear(color);
}


void Video::draw(sf::Drawable& drawable)
{
	m_window->draw(drawable);
}


void Video::draw(sf::Drawable& drawable, sf::RenderStates& renderStates)
{
	m_window->draw(drawable, renderStates);
}


static sf::CircleShape circleDrawPoint;
void Video::drawPoint(const float positionX, const float positionY, const sf::Color color)
{
	circleDrawPoint.setRadius(1);
	circleDrawPoint.setFillColor(color);
	circleDrawPoint.setPosition(positionX, positionY);

	m_window->draw(circleDrawPoint);
}


static sf::RectangleShape rectangleDrawRectangle;
void Video::drawRectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color)
{
	rectangleDrawRectangle.setPosition(position.x, position.y);
	rectangleDrawRectangle.setSize(sf::Vector2f(size.x, size.y));
	rectangleDrawRectangle.setFillColor(color);

	m_window->draw(rectangleDrawRectangle);
}
