#include "Video.hpp"
#include "../Defines.hpp"


Video::Video(unsigned int sizeX, unsigned int sizeY)
{
	init(sizeX, sizeY);
}


Video::~Video()
{
	end();
}


void Video::init(unsigned int sizeX, unsigned int sizeY)
{
	initWindow(sizeX, sizeY);

	/*glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Normal blending

	glClearColor(0, 0, 0, 0);

	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	m_window.setKeyRepeatEnabled(false);
	m_window.clear();
}


void Video::initWindow(unsigned int sizeX, unsigned int sizeY)
{
	m_window.create(sf::VideoMode(sizeX, sizeY), "Demo");

	m_window.setFramerateLimit(FPS_LIMIT);
	//m_window.setVerticalSyncEnabled(true);

	if (!m_window.isOpen())
	{
		//DEBUG.error(__LINE__, "Error at Init Window");
		exit(ERROR_INIT);
	}

	//this->debugDraw.LinkTarget(m_window);
}


void Video::end()
{
	m_window.close();
}


void Video::swapBuffers()
{
	m_window.display();
}


/*void Video::setZBuffer(bool set)
{
	if (set)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}*/


/*void Video::setRender2D()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1000.0, 1000.0);
	//glOrtho(0, GAME_SCREEN_X, GAME_SCREEN_Y, 0, -1000.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/


/*void Video::setRender3D()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, (GLfloat)GAME_SCREEN_X / (GLfloat)GAME_SCREEN_Y, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/


sf::Vector2u Video::getSize()
{
	return m_window.getSize();
}


sf::RenderWindow* Video::getWindow()
{
	return &m_window;
}


sf::Vector2f* Video::getCameraPosition()
{
	return &m_cameraPosition;
}


void Video::viewReset(sf::FloatRect rect)
{
	sf::View view = m_window.getView();

	view.reset(rect);

	m_window.setView(view);
}


void Video::viewResetToCamera()
{
	viewReset(sf::FloatRect(getCameraPosition()->x, getCameraPosition()->y, getSize().x, getSize().y));
}


void Video::clear(sf::Color color)
{
    m_window.clear(color);
}


void Video::draw(sf::Drawable& drawable)
{
    m_window.draw(drawable);
}


static sf::CircleShape circleDrawPoint;
void Video::drawPoint(const float positionX, const float positionY, const sf::Color color)
{
	circleDrawPoint.setRadius(1);
	circleDrawPoint.setFillColor(color);
	circleDrawPoint.setPosition(positionX, positionY);

	m_window.draw(circleDrawPoint);
}


static sf::RectangleShape rectangleDrawRectangle;
void Video::drawRectangle(const sf::Vector2f position, const sf::Vector2f size, const sf::Color color)
{
	rectangleDrawRectangle.setPosition(position.x, position.y);
	rectangleDrawRectangle.setSize(sf::Vector2f(size.x, size.y));
	rectangleDrawRectangle.setFillColor(color);

	m_window.draw(rectangleDrawRectangle);
}
