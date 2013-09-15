#include "TetrisController.hpp"
#include <stdlib.h>


int Tetris::blockInfoColor[] =
{
	0, 1, 2, 2, 3, 4, 4, 1, 0, 3
};

int Tetris::blockInfo[10][4*4] =
{
	{ // Barra
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
	},
	{ // Cuadrado
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{ // L Derecha
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0,
	},
	{ // L Izquierda
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0,
	},
	{ // T
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
	},
	{ // Z Derecha
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
	},
	{ // Z Izquierda
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0,
	}, // I Grande [Hard]
	{
		1, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0
	}, // T Grande [Hard]
	{
		1, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}, // C Grande [Hard]
	{
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0
	}
};


Tetris::Tetris()
{
	if (!m_scoreFont.loadFromFile("resources/arial.ttf"))
	{
		stop();
	}

	if (!m_collideSound.loadFromFile("resources/pong.wav"))
	{
		stop();
	}

	if (!m_scoreSound.loadFromFile("resources/ping.wav"))
	{
		stop();
	}

	m_screenSize = sf::Vector2i(640, 480);
	m_blockSize = sf::Vector2i(16, 16);
	m_blockStackSize = sf::Vector2i(10, 28);
	m_blockPlayerStackSize = sf::Vector2i(4, 4);

	for(int y = 0; y < m_blockStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockStackSize.x; ++x)
		{
			m_blockStack.push_back(BlockInfo());
		}
	}

	for(int y = 0; y < m_blockPlayerStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockPlayerStackSize.x; ++x)
		{
			m_blockPlayerStack.push_back(BlockInfo());
		}
	}

	m_hardMode = false;

	m_video->changeTitle("Tetris");

	reset();
}


void Tetris::onTick()
{
	if(m_input->getKeyPress()->Left.value)
	{
		if(!checkCollision(m_playerPosition - sf::Vector2i(1, 0)))
		{
			m_playerPosition.x -= 1;

			m_sliderTimer.start();
		}
		else
		{
			m_sound.setBuffer(m_collideSound);
			m_sound.play();
		}
	}
	else if(m_input->getKeyPress()->Right.value)
	{
		if(!checkCollision(m_playerPosition + sf::Vector2i(1, 0)))
		{
			m_playerPosition.x += 1;

			m_sliderTimer.start();
		}
		else
		{
			m_sound.setBuffer(m_collideSound);
			m_sound.play();
		}
	}
	else if(m_input->getKeyPress()->Down.value)
	{
		if(!checkCollision(m_playerPosition + sf::Vector2i(0, 1)))
		{
			m_playerPosition.y += 1;

			m_sliderTimer.start();
		}
		else
		{
			changePlayerBlock();
		}
	}
	else if(m_input->getKeyPress()->Space.value)
	{
		rotatePlayerBlocks();
	}
	else if(m_input->getKeyHeld()->Left.value && m_sliderTimer.getTicks() > 350)
	{
		if(!checkCollision(m_playerPosition - sf::Vector2i(1, 0)))
		{
			m_playerPosition.x -= 1;
		}
	}
	else if(m_input->getKeyHeld()->Right.value && m_sliderTimer.getTicks() > 350)
	{
		if(!checkCollision(m_playerPosition + sf::Vector2i(1, 0)))
		{
			m_playerPosition.x += 1;
		}
	}
	else if(m_input->getKeyHeld()->Down.value && m_sliderTimer.getTicks() > 250)
	{
		if(!checkCollision(m_playerPosition + sf::Vector2i(0, 1)))
		{
			m_playerPosition.y += 1;
		}
		else
		{
			changePlayerBlock();

			m_sliderTimer.stop();
		}

		return;
	}

	if(m_input->getKeyUp()->Up.value || m_input->getKeyUp()->Left.value || m_input->getKeyUp()->Right.value)
	{
		if(!m_input->getKeyHeld()->Down.value && !m_input->getKeyHeld()->Left.value && !m_input->getKeyHeld()->Right.value)
		{
			m_sliderTimer.stop();
		}
	}

	if(m_timingTimer.getTicks() - m_lastUpdateTime < 300)
	{
		return;
	}
	else
	{
		m_lastUpdateTime = m_timingTimer.getTicks();
	}

	if(!checkCollision(m_playerPosition + sf::Vector2i(0, 1)))
	{
		m_playerPosition.y += 1;
	}
	else
	{
		changePlayerBlock();
	}
}


void Tetris::onRender()
{
	m_video->clear(sf::Color::White);

	m_video->drawRectangle(sf::Vector2f(0, 0), sf::Vector2f(m_screenSize.x, 16), sf::Color::Black);
	m_video->drawRectangle(sf::Vector2f(0, m_screenSize.y - 16), sf::Vector2f(m_screenSize.x, 16), sf::Color::Black);

	m_video->drawRectangle(sf::Vector2f(0, 0), sf::Vector2f((m_screenSize.x / 2) - ((m_blockStackSize.x * m_blockSize.x) / 2), m_screenSize.y), sf::Color::Black);
	m_video->drawRectangle(sf::Vector2f((m_screenSize.x / 2) + ((m_blockStackSize.x * m_blockSize.x) / 2), 0), sf::Vector2f(m_screenSize.x, m_screenSize.y), sf::Color::Black);

	m_video->drawRectangle(
		sf::Vector2f((m_screenSize.x / 2) + ((m_blockStackSize.x * m_blockSize.x) / 2) + m_blockSize.x, m_blockSize.x),
		sf::Vector2f(m_blockPlayerStackSize.x * m_blockSize.x, m_blockPlayerStackSize.y * m_blockSize.y), sf::Color::White);

	// Dibujar bloques del tablero
	for(int y = 0; y < m_blockStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockStackSize.x; ++x)
		{
			int index = x + (y * m_blockStackSize.x);
			BlockInfo* block = &m_blockStack[index];

			if(block->isBlock)
			{
				int posX = (m_screenSize.x / 2) - ((m_blockStackSize.x * m_blockSize.x) / 2) + (m_blockSize.x * x);
				int posY = (m_blockSize.y * y) + 16;

				sf::Color color = getColor(blockInfoColor[block->color]);

				m_video->drawRectangle(sf::Vector2f(posX, posY), sf::Vector2f(m_blockSize.x, m_blockSize.y), sf::Color(75, 75, 75));
				m_video->drawRectangle(sf::Vector2f(posX + 1, posY + 1), sf::Vector2f(m_blockSize.x - 2, m_blockSize.y - 2), color);
			}
		}
	}

	// Dibujar bloques del jugador
	for(int y = 0; y < m_blockPlayerStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockPlayerStackSize.x; ++x)
		{
			int index = x + (y * m_blockPlayerStackSize.x);
			BlockInfo* block = &m_blockPlayerStack[index];

			if(block->isBlock)
			{
				int posX = (m_screenSize.x / 2) - ((m_blockStackSize.x * m_blockSize.x) / 2) + (m_blockSize.x * x) + (m_playerPosition.x * m_blockSize.x);
				int posY = (m_blockSize.y * y) + 16 + (m_playerPosition.y * m_blockSize.y);

				sf::Color color = getColor(blockInfoColor[block->color]);

				m_video->drawRectangle(sf::Vector2f(posX, posY), sf::Vector2f(m_blockSize.x, m_blockSize.y), sf::Color(200, 50, 50));
				m_video->drawRectangle(sf::Vector2f(posX + 1, posY + 1), sf::Vector2f(m_blockSize.x - 2, m_blockSize.y - 2), color);
			}
		}
	}

	// Dibujar bloques de la siguiente ronda
	for(int y = 0; y < m_blockPlayerStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockPlayerStackSize.x; ++x)
		{
			int index = x + (y * m_blockPlayerStackSize.x);

			if(blockInfo[m_nextBlockId][index] == 1)
			{
				int posX = (m_screenSize.x / 2) + ((m_blockStackSize.x * m_blockSize.x) / 2) + (m_blockSize.x * x) + 16;
				int posY = (m_blockSize.y * y) + 16;

				sf::Color color = getColor(blockInfoColor[m_nextBlockId]);

				m_video->drawRectangle(sf::Vector2f(posX, posY), sf::Vector2f(m_blockSize.x, m_blockSize.y), sf::Color(50, 50, 200));
				m_video->drawRectangle(sf::Vector2f(posX + 1, posY + 1), sf::Vector2f(m_blockSize.x - 2, m_blockSize.y - 2), color);
			}
		}
	}

	char temp[256];
	sprintf(temp, "Score: %i", m_playerScore);

	sf::Text score;
	score.setFont(m_scoreFont);
	score.setString(temp);
	score.setCharacterSize(24);
	score.setColor(sf::Color::White);
	score.setPosition((m_screenSize.x / 2) + ((m_blockStackSize.x * m_blockSize.x) / 2) + 16, (m_screenSize.y - 48));
	m_video->draw(score);

	score.setPosition((m_screenSize.x / 2) + ((m_blockStackSize.x * m_blockSize.x) / 2) + 16, (m_screenSize.y - 80));
	score.setString((m_hardMode ? "Hard Mode" : "Normal Mode"));
	m_video->draw(score);

	m_video->swapBuffers();
}


void Tetris::onEvent(const int eventType, const int param1, const int param2)
{
	m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_KEYDOWN:
			switch (param1)
			{
				case KeyId::F3:
					m_hardMode = !m_hardMode;
					reset();
					break;
				case KeyId::F2:
					if(m_sound.getVolume() > 0)
					{
						m_sound.setVolume(0);
					}
					else
					{
						m_sound.setVolume(100);
					}
					break;

				case KeyId::Escape:
					stop();
					break;

				case KeyId::F1:
					reset();
					break;
			}
			break;

		case EVENT_QUIT:
			stop();

			break;
	}
}


void Tetris::reset()
{
	m_playerScore = 0;
	m_playerPosition = sf::Vector2i((int)((m_blockStackSize.x / 2)-(m_blockPlayerStackSize.x / 2)), 0);

	for(int y = 0; y < m_blockStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockStackSize.x; ++x)
		{
			int index = x + (y * m_blockStackSize.x);

			m_blockStack[index].isBlock = false;
			m_blockStack[index].color  = 0;
		}
	}

	changeNextBlock();
	m_playerBlockId = m_nextBlockId;
	changeNextBlock();

	copyBlockInfoToPlayer();

	m_timingTimer.start();
	m_lastUpdateTime = m_timingTimer.getTicks();
}


sf::Color Tetris::getColor(unsigned int colorId)
{
	sf::Color color;

	switch(colorId)
	{
		case 0:
			color = sf::Color::Blue;
			break;
		case 1:
			color = sf::Color::Red;
			break;
		case 2:
			color = sf::Color::Yellow;
			break;
		case 3:
			color = sf::Color::Green;
			break;
		case 4:
			color = sf::Color::Cyan;
			break;
		default:
			color = sf::Color::Magenta;
			break;
	}

	return color;
}


void Tetris::changeNextBlock()
{
	if(m_hardMode && (rand() % 100 > 35))
	{
		m_nextBlockId = (rand() % 10);
	}
	else
	{
		m_nextBlockId = (rand() % 7);
	}
}


bool Tetris::checkCollision(sf::Vector2i playerPosition)
{
	for(int y = 0; y < m_blockPlayerStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockPlayerStackSize.x; ++x)
		{
			int indexPlayer = x + (y * m_blockPlayerStackSize.x);

			if(m_blockPlayerStack[indexPlayer].isBlock)
			{
				int indexStack = (x + playerPosition.x) + ((y + playerPosition.y) * m_blockStackSize.x);

				if(m_blockStack[indexStack].isBlock)
				{
					return true;
				}

				if(playerPosition.y + (y + 1) > m_blockStackSize.y)
				{
					return true;
				}

				if((x + playerPosition.x) < 0)
				{
					if(m_blockPlayerStack[indexPlayer].isBlock)
					{
						return true;
					}
				}
				else if((x + playerPosition.x) >= m_blockStackSize.x)
				{
					if(m_blockPlayerStack[indexPlayer].isBlock)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}


void Tetris::copyBlockInfoToPlayer()
{
	for(int x = 0; x < (m_blockPlayerStackSize.x * m_blockPlayerStackSize.y); ++x)
	{
		m_blockPlayerStack[x].isBlock = false;

		if(blockInfo[m_playerBlockId][x] == 1)
		{
			m_blockPlayerStack[x].isBlock = true;
			m_blockPlayerStack[x].color =  m_playerBlockId;
		}
	}
}


void Tetris::copyPlayerToBoard()
{
	for(int y = 0; y < m_blockPlayerStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockPlayerStackSize.x; ++x)
		{
			int indexPlayer = x + (y * m_blockPlayerStackSize.x);

			if(m_blockPlayerStack[indexPlayer].isBlock)
			{
				int indexStack = (x + m_playerPosition.x) + ((y + m_playerPosition.y) * m_blockStackSize.x);

				m_blockStack[indexStack].isBlock = true;
				m_blockStack[indexStack].color = m_blockPlayerStack[indexPlayer].color;
			}
		}
	}
}

void Tetris::changePlayerBlock()
{
	copyPlayerToBoard();
	m_playerBlockId = m_nextBlockId;
	changeNextBlock();
	copyBlockInfoToPlayer();
	m_playerPosition = sf::Vector2i((int)((m_blockStackSize.x / 2)-(m_blockPlayerStackSize.x / 2)), 0);

	if(checkCollision(m_playerPosition))
	{
		reset();
	}

	if(!checkLinesBoard())
	{
		m_sound.setBuffer(m_collideSound);
		m_sound.play();
	}
	else
	{
		m_sound.setBuffer(m_scoreSound);
		m_sound.play();
	}
}

bool Tetris::checkLinesBoard()
{
	bool hasLines = false;

	for(int y = (m_blockStackSize.y - 1); y >= 0; --y)
	{
		for(int x = 0; x < m_blockStackSize.x; ++x)
		{
			int index = x + (y * m_blockStackSize.x);

			if(!m_blockStack[index].isBlock)
			{
				break;
			}

			if((x + 1) == m_blockStackSize.x)
			{
				hasLines = true;
				m_playerScore += 10;

				for(int yErase = y; yErase >= 0; --yErase)
				{
					for(int xErase = 0; xErase < m_blockStackSize.x; ++xErase)
					{
						int indexErase = xErase + (yErase * m_blockStackSize.x);

						if(yErase > 0)
						{
							int indexEraseCopy = xErase + ((yErase - 1) * m_blockStackSize.x);

							m_blockStack[indexErase].isBlock = m_blockStack[indexEraseCopy].isBlock;
						}
						else
						{
							m_blockStack[indexErase].isBlock = false;
						}
					}
				}
			}
		}
	}

	return hasLines;
}


void Tetris::rotatePlayerBlocks()
{
	std::vector<BlockInfo> buffer(m_blockPlayerStack);

	for(int y = 0; y < m_blockPlayerStackSize.y; ++y)
	{
		for(int x = 0; x < m_blockPlayerStackSize.x; ++x)
		{
			int indexPlayer = ((m_blockPlayerStackSize.x - 1) - y) + (x * m_blockPlayerStackSize.x);
			int indexBuffer = x + (y * m_blockPlayerStackSize.x);

			m_blockPlayerStack[indexPlayer].isBlock = buffer[indexBuffer].isBlock;
			m_blockPlayerStack[indexPlayer].color = buffer[indexBuffer].color;
		}
	}

	if(checkCollision(m_playerPosition))
	{
		m_blockPlayerStack = buffer;
	}
}
