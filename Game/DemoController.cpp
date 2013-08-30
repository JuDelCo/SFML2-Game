#include "DemoController.hpp"


int level[] =
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
    m_tileMap->update();
}


void TechDemo::onRender()
{
	sf::RenderWindow* window = m_video->getWindow();

    window->clear(sf::Color::Black);

    sf::View view = window->getView();
    view.reset(sf::FloatRect(m_video->getCameraPosition()->x, m_video->getCameraPosition()->y, m_video->getSize().x, m_video->getSize().y));
    window->setView(view);

    window->draw(*m_tileMap);

	m_video->swapBuffers();
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

		case EVENT_MOUSEMOTION:
			if (m_input->getMouse()->held.right)
			{
				m_video->getCameraPosition()->x -= (m_input->getMouse()->xRel);
				m_video->getCameraPosition()->y -= (m_input->getMouse()->yRel);
			}
			break;

        case EVENT_MOUSEDOWN:
            if (m_input->getMouse()->press.left)
            {
                m_tileMap->setTile(m_tileMap->getTilePos(sf::Vector2u(m_input->getMouse()->x, m_input->getMouse()->y)), 2);
            }

            break;

		case EVENT_QUIT:
			stop();
			break;
	}
}


void TechDemo::reset()
{

}


void TechDemo::end()
{

}