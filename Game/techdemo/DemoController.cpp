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

	if (!m_textureTest.loadFromFile("resources/tileset_pacman_ghost.png"))
	{
		stop();
	}

	m_spriteTest.setSize(sf::Vector2i(15,15));
	m_spriteTest.bindTexture(TexturePtr(&m_textureTest));
	m_spriteTest.setOrigin(7.5,7.5);
	m_spriteTest.setScale(4,4);
	m_spriteTest.setRotation(45);

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

	m_spriteTest.setPosition(100,350);
	m_spriteTest.setFrame(0);
	m_spriteTest.setColor(sf::Color::Red);
	m_spriteTest.flipHorizontal(false);
	m_spriteTest.flipVertical(false);
	m_video->draw(m_spriteTest);

	m_spriteTest.setPosition(200,350);
	m_spriteTest.setFrame(1);
	m_spriteTest.setColor(sf::Color::Yellow);
	m_spriteTest.flipHorizontal(true);
	m_spriteTest.flipVertical(false);
	m_video->draw(m_spriteTest);

	m_spriteTest.setPosition(300,350);
	m_spriteTest.setFrame(0);
	m_spriteTest.setColor(sf::Color::Blue);
	m_spriteTest.flipHorizontal(false);
	m_spriteTest.flipVertical(true);
	m_video->draw(m_spriteTest);

	m_spriteTest.setPosition(400,350);
	m_spriteTest.setFrame(1);
	m_spriteTest.setColor(sf::Color::Green);
	m_spriteTest.flipHorizontal(true);
	m_spriteTest.flipVertical(true);
	m_video->draw(m_spriteTest);

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

		m_tileMap->setTile(tileMousePointed, (rand() % 4));
	}
}


void TechDemo::onQuit()
{
	stop();
}
