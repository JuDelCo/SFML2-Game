#include "DemoController.hpp"


const int level[] =
{
    0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0,
    2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 2, 0, 0, 3, 0, 1, 1, 1, 0, 2, 2, 2, 0, 0, 0,
    0, 2, 2, 0, 1, 1, 1, 0, 0, 0, 2, 2, 2, 3, 0, 0,
    0, 0, 2, 0, 1, 0, 3, 3, 0, 0, 2, 2, 2, 2, 3, 0,
    3, 0, 2, 0, 1, 0, 3, 3, 3, 0, 2, 2, 2, 2, 2, 2,
    0, 0, 2, 0, 1, 3, 3, 3, 0, 0, 0, 0, 2, 2, 2, 2,
};

TechDemo::TechDemo() : GameBase(1024, 768)
{
    m_tileMap = new TileMap("resources/tileset.png", sf::Vector2u(32, 32), level, 16, 8);

	reset();
}


TechDemo::~TechDemo()
{

}


void TechDemo::init()
{

}


void TechDemo::onTick()
{

}


void TechDemo::onRender()
{
	sf::RenderWindow* window = VIDEO->getWindow();

    window->clear(sf::Color::Black);
    window->draw(*m_tileMap);

	VIDEO->swapBuffers();
}


void TechDemo::onEvent(const int eventType, const int param1, const int param2)
{
	m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_KEYDOWN:
			switch (param1)
			{
				case KEY::Escape:
					stop();
					break;

				case KEY::F1:
					reset();
					break;
			}

			break;

		case EVENT_QUIT:
			stop();
	}
}


void TechDemo::reset()
{

}


void TechDemo::end()
{

}
