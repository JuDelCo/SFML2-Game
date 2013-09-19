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


TechDemo::TechDemo()
{
	m_tileMap = new TileMap("resources/tileset.png", sf::Vector2u(32, 32), level, 16, 8);

	m_video->changeTitle("TechDemo");

	m_input->EventKeyDown.connect(Event::CreateCallBack(this, &TechDemo::onKeyDown));
	m_input->EventMouseMotion.connect(Event::CreateCallBack(this, &TechDemo::onMouseMotion));
	m_input->EventMouseDown.connect(Event::CreateCallBack(this, &TechDemo::onMouseDown));
	m_input->EventQuit.connect(Event::CreateCallBack(this, &TechDemo::onQuit));
}


TechDemo::~TechDemo()
{
	delete m_tileMap;
}


void TechDemo::onTick()
{
	m_tileMap->update();
}


void TechDemo::onRender()
{
	m_video->clear(sf::Color::Black);

	m_video->viewResetToCamera();

	m_video->draw(*m_tileMap);

	m_video->swapBuffers();
}


void TechDemo::onKeyDown(int keyCode)
{
	if(keyCode == KeyId::Escape)
	{
		stop();
	}
}


void TechDemo::onMouseMotion(sf::Vector2i mousePosition)
{
	if (m_input->getMouse()->held.right)
	{
		m_video->moveCameraPosition(sf::Vector2i(m_input->getMouse()->xRel, m_input->getMouse()->yRel));
	}
}


void TechDemo::onMouseDown(sf::Mouse::Button mouseButton)
{
	if (m_input->getMouse()->press.left)
	{
		sf::Vector2i mousePositionWorld = m_input->getMousePos() + m_video->getCameraPosition();

		sf::Vector2u tileMousePointed = m_tileMap->getTilePos(sf::Vector2u(mousePositionWorld));

		m_tileMap->setTile(tileMousePointed, 2); // 2 = Test
	}
}


void TechDemo::onQuit()
{
	stop();
}
