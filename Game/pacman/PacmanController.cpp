#include "PacmanController.hpp"
#include <stdlib.h>


Pacman::Pacman() : GameBase(640, 480)
{
	bool errorLoading = false;

	if (!m_textFont.loadFromFile("resources/arial.ttf"))
	{
		errorLoading = true;
	}
	else if (!m_mapTileSet.loadFromFile("resources/tileset_pacman_map.png"))
	{
		errorLoading = true;
	}
	else if (!m_player.TileSet.loadFromFile("resources/tileset_pacman_player.png"))
	{
		errorLoading = true;
	}
	else if (!m_ghostTileSet.loadFromFile("resources/tileset_pacman_ghost.png"))
	{
		errorLoading = true;
	}
	else if (!m_killSound.loadFromFile("resources/pacman_kill.wav"))
	{
		errorLoading = true;
	}
	else if (!m_deadSound.loadFromFile("resources/pacman_dead.wav"))
	{
		errorLoading = true;
	}
	else if (!m_ballSound.loadFromFile("resources/pacman_ball.wav"))
	{
		errorLoading = true;
	}
	else if (!m_powerupSound.loadFromFile("resources/pacman_powerup.wav"))
	{
		errorLoading = true;
	}

	if(errorLoading)
	{
		stop();

		return;
	}

	srand(time(NULL));

	m_screenSize = sf::Vector2i(640, 480);
	m_mapSize = sf::Vector2i(28, 31);
	m_tileSize = sf::Vector2i(15, 15);
	m_mapNullCell = (m_mapSize.x * m_mapSize.y);
	m_mapVertexArray.resize(m_mapSize.x * m_mapSize.y * 4);
	m_mapVertexArray.setPrimitiveType(sf::Quads);
	m_mapScreenOffset = sf::Vector2i((m_screenSize.x - (m_mapSize.x * m_tileSize.x)) / 2, (m_screenSize.y - (m_mapSize.y * m_tileSize.y)) / 2);
	m_player.Sprite = sf::Sprite(m_player.TileSet);
	m_player.Sprite.setOrigin(sf::Vector2f(m_tileSize.x / 2, m_tileSize.y / 2));
	m_liveSprite = sf::Sprite(m_mapTileSet);
	m_liveSprite.setTextureRect(sf::IntRect((5 * m_tileSize.x), 0, m_tileSize.x, m_tileSize.y));

	for(int x = 0; x < 4; ++x)
	{
		m_ghost[x].Sprite = sf::Sprite(m_ghostTileSet);
	}

	// Inicializar tileMap y posición de sus Quads (VertexArray)
	for(int y = 0; y < m_mapSize.y; ++y)
	{
		for(int x = 0; x < m_mapSize.x; ++x)
		{
			sf::Vertex quad[4];

			quad[0].position = sf::Vector2f(x * m_tileSize.x, y * m_tileSize.y) + sf::Vector2f(m_mapScreenOffset);
			quad[1].position = sf::Vector2f((x + 1) * m_tileSize.x, y * m_tileSize.y) + sf::Vector2f(m_mapScreenOffset);
			quad[2].position = sf::Vector2f((x + 1) * m_tileSize.x, (y + 1) * m_tileSize.y) + sf::Vector2f(m_mapScreenOffset);
			quad[3].position = sf::Vector2f(x * m_tileSize.x, (y + 1) * m_tileSize.y) + sf::Vector2f(m_mapScreenOffset);

			unsigned int index = (x + (y * m_mapSize.x)) * 4;

			m_mapVertexArray[index + 0] = quad[0];
			m_mapVertexArray[index + 1] = quad[1];
			m_mapVertexArray[index + 2] = quad[2];
			m_mapVertexArray[index + 3] = quad[3];
		}
	}

	if(loadMap())
	{
		reset();
	}
	else
	{
		stop();
	}
}


Pacman::~Pacman()
{
	// Nada (No hay ningun puntero a objeto en la clase)
}


void Pacman::init()
{
	// Nada
}


void Pacman::onTick()
{
	// Cambiar dirección deseada de Pacman
	if(m_input->getKeyPress()->Up.value)
	{
		m_player.DesiredDirection = ViewDirection::Up;
	}
	else if(m_input->getKeyPress()->Right.value)
	{
		m_player.DesiredDirection = ViewDirection::Right;
	}
	else if(m_input->getKeyPress()->Left.value)
	{
		m_player.DesiredDirection = ViewDirection::Left;
	}
	else if(m_input->getKeyPress()->Down.value)
	{
		m_player.DesiredDirection = ViewDirection::Down;
	}

	if(m_readyTimer.getTicks() > 0)
	{
		if(m_readyTimer.getTicks() >= 2000)
		{
			m_readyTimer.stop();
			m_gameTimer.start();
			m_frameTimer.start();
		}

		return;
	}

	if(m_pauseTimer.getTicks() > 0)
	{
		if(m_pauseTimer.getTicks() >= 500)
		{
			m_pauseTimer.stop();

			m_gameTimer.resume();
			m_frameTimer.resume();
			if(m_ghostKillTimer.isPaused())
			{
				m_ghostKillTimer.resume();
			}

			if(m_player.IsDead)
			{
				resetGame();
			}
		}

		return;
	}

	// Animar Pacman y Fantasmas (Cambio de Frames)
	if(m_frameTimer.getTicks() > 50)
	{
		if(m_player.Moving)
		{
			m_player.CurrentFrame++;

			if(m_player.CurrentFrame > 3)
			{
				m_player.CurrentFrame = 0;
			}
		}
		else
		{
			m_player.CurrentFrame = 1;
		}

		for(unsigned int x = 0; x < m_ghostCount; ++x)
		{
			m_ghost[x].CurrentFrame++;

			if(m_ghost[x].CurrentFrame > 1)
			{
				m_ghost[x].CurrentFrame = 0;
			}
		}

		m_frameTimer.start();
	}

	// Mover Pacman
	moveEntity(&m_player.CurrentCellIndex, &m_player.PositionOffset, &m_player.Direction, &m_player.DesiredDirection, &m_player.Moving, m_player.MoveSpeed, true);

	bool ghostForceRefresh = false;

	sf::Vector2i findCoin = sf::Vector2i(m_player.CurrentCellIndex % m_mapSize.x, floor(m_player.CurrentCellIndex / m_mapSize.x));

	// Comer bolas (Pacman) y actualizar mapa
	for(unsigned int x = 0; x < m_ballPosition.size(); ++x)
	{
		if(m_ballPosition[x] == findCoin)
		{
			mapSetCell(m_player.CurrentCellIndex, CellType::Nothing);

			m_ballPosition.erase(m_ballPosition.begin() + x);

			addScore(10);

			m_sound.setBuffer(m_ballSound);
			m_sound.play();

			if(m_ballPosition.empty() && m_ballBigPosition.empty())
			{
				resetGame();

				return;
			}
		}
	}

	for(unsigned int x = 0; x < m_ballBigPosition.size(); ++x)
	{
		if(m_ballBigPosition[x] == findCoin)
		{
			mapSetCell(m_player.CurrentCellIndex, CellType::Nothing);

			m_ballBigPosition.erase(m_ballBigPosition.begin() + x);

			m_powerupKillCounter = 0;
			m_ghostKillTimer.start();
			ghostForceRefresh = true;

			m_sound.setBuffer(m_powerupSound);
			m_sound.play();

			for(unsigned int x = 0; x < m_ghostCount; ++x)
			{
				m_ghost[x].Invulnerable = false;
			}

			addScore(50);

			if(m_ballPosition.empty() && m_ballBigPosition.empty())
			{
				resetGame();

				return;
			}
		}
	}

	if(m_ghostKillTimer.getTicks() > 7000)
	{
		m_ghostKillTimer.stop();

		for(unsigned int x = 0; x < m_ghostCount; ++x)
		{
			m_ghost[x].Invulnerable = false;

			m_ghost[x].LastStateChange = m_gameTimer.getTicks();
			m_ghost[x].StateDuration = 3000;
			m_ghost[x].IsInChase = true;
		}

		ghostForceRefresh = true;
	}

	// IA Fantasmas
	for(unsigned int x = 0; x < m_ghostCount; ++x)
	{
		if(m_ghost[x].TimeToRelease >= m_gameTimer.getTicks())
		{
			break;
		}

		unsigned int ignoreCell;

		if(m_ghost[x].Direction == ViewDirection::Left)
		{
			ignoreCell = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Right);
		}
		else if(m_ghost[x].Direction == ViewDirection::Right)
		{
			ignoreCell = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Left);
		}
		else if(m_ghost[x].Direction == ViewDirection::Up)
		{
			ignoreCell = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Down);
		}
		else
		{
			ignoreCell = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Up);
		}

		float ghostMoveSpeed = m_ghostKillTimer.isStarted() && (m_ghost[x].IsDead ? false : !m_ghost[x].Invulnerable) ?
			(m_ghost[x].MoveSpeed / 2) :
			(m_ghost[x].IsDead ? m_ghost[x].MoveSpeed * 1.5: m_ghost[x].MoveSpeed);

		if(m_ghost[x].CurrentCellIndex == m_ghost[x].HomeIndex)
		{
			m_ghost[x].IsDead = false;

			if(m_ghostKillTimer.isStarted())
			{
				m_ghost[x].Invulnerable = true;
			}

			m_ghost[x].LastStateChange = m_gameTimer.getTicks();
			m_ghost[x].StateDuration = 1000;
			m_ghost[x].IsInChase = true;
		}

		if(m_gameTimer.getTicks() >= (m_ghost[x].LastStateChange + m_ghost[x].StateDuration))
		{
			if(!m_ghostKillTimer.isStarted())
			{
				ghostForceRefresh = true;
			}

			m_ghost[x].LastStateChange = m_gameTimer.getTicks();

			if(m_ghost[x].IsInChase)
			{
				m_ghost[x].IsInChase = false;
				m_ghost[x].StateDuration = (3000 + (rand() % 3000));
			}
			else
			{
				m_ghost[x].IsInChase = true;
				m_ghost[x].StateDuration = (5000 + (rand() % 3000));
			}
		}

		if(m_ghost[x].LastCellChecked != m_ghost[x].CurrentCellIndex || ghostForceRefresh)
		{
			if(m_ghost[x].IsDead)
			{
				m_ghost[x].DesiredDirection = getNextDirection(m_ghost[x].CurrentCellIndex, m_ghost[x].HomeIndex, ignoreCell);

			}
			else if(m_ghost[x].IsInChase && (!m_ghostKillTimer.isStarted() || m_ghost[x].Invulnerable))
			{
				if(m_ghost[x].CurrentCellIndex != m_player.CurrentCellIndex)
				{
					m_ghost[x].DesiredDirection = getNextDirection(m_ghost[x].CurrentCellIndex, m_player.CurrentCellIndex, ignoreCell);
				}
			}
			else
			{
				unsigned int tempIndex;
				std::vector<unsigned int> possibleCells;

				if(m_ghost[x].Direction != ViewDirection::Left)
				{
					tempIndex = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Left);

					if(tempIndex != ignoreCell && m_mapInfo[tempIndex] != CellType::Wall)
					{
						possibleCells.push_back(tempIndex);
					}
				}

				if(m_ghost[x].Direction != ViewDirection::Right)
				{
					tempIndex = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Right);

					if(tempIndex != ignoreCell && m_mapInfo[tempIndex] != CellType::Wall)
					{
						possibleCells.push_back(tempIndex);
					}
				}

				if(m_ghost[x].Direction != ViewDirection::Up)
				{
					tempIndex = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Up);

					if(tempIndex != ignoreCell && m_mapInfo[tempIndex] != CellType::Wall)
					{
						possibleCells.push_back(tempIndex);
					}
				}

				if(m_ghost[x].Direction != ViewDirection::Down)
				{
					tempIndex = getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Down);

					if(tempIndex != ignoreCell && m_mapInfo[tempIndex] != CellType::Wall)
					{
						possibleCells.push_back(tempIndex);
					}
				}

				// Si hay caminos alternativos a seguir (Que no sea ni a donde se dirige ni la casilla anterior) o es un callejón sin salida...
				if(possibleCells.size() > 0 || getMapInfo(m_ghost[x].CurrentCellIndex, m_ghost[x].Direction) == CellType::Wall)
				{
					m_ghost[x].DesiredDirection = getRandomDirection(m_ghost[x].CurrentCellIndex, ignoreCell);
				}
			}

			m_ghost[x].LastCellChecked = m_ghost[x].CurrentCellIndex;
		}

		moveEntity(&m_ghost[x].CurrentCellIndex, &m_ghost[x].PositionOffset, &m_ghost[x].Direction, &m_ghost[x].DesiredDirection, &m_ghost[x].Moving, ghostMoveSpeed, false);

		if(!m_ghost[x].IsDead)
		{
			// Calcular colisión con Pacman
			if(m_ghost[x].CurrentCellIndex == m_player.CurrentCellIndex)
			{
				ghostCollide(x);
			}
			else if(getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Left) == m_player.CurrentCellIndex)
			{
				if((m_player.PositionOffset.x + (m_tileSize.x / 2)) - (m_ghost[x].PositionOffset.x + (m_tileSize.x / 2)) >= 0)
				{
					ghostCollide(x);
				}
			}
			else if(getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Right) == m_player.CurrentCellIndex)
			{
				if((m_ghost[x].PositionOffset.x + (m_tileSize.x / 2)) - (m_player.PositionOffset.x + (m_tileSize.x / 2)) >= 0)
				{
					ghostCollide(x);
				}
			}
			else if(getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Up) == m_player.CurrentCellIndex)
			{
				if((m_player.PositionOffset.y + (m_tileSize.y / 2)) - (m_ghost[x].PositionOffset.y + (m_tileSize.y / 2)) >= 0)
				{
					ghostCollide(x);
				}
			}
			else if(getMapIndex(m_ghost[x].CurrentCellIndex, ViewDirection::Down) == m_player.CurrentCellIndex)
			{
				if((m_ghost[x].PositionOffset.y + (m_tileSize.y / 2)) - (m_player.PositionOffset.y + (m_tileSize.y / 2)) >= 0)
				{
					ghostCollide(x);
				}
			}
		}
	}
}


void Pacman::onRender()
{
	m_video->clear(sf::Color::Black);

	// Dibujar TileMap
	sf::RenderStates renderStates;
	renderStates.texture = &m_mapTileSet;
	m_video->getWindow()->draw(m_mapVertexArray, renderStates);

	bool invertY = false;

	// Dibujar Pacman
	switch(m_player.Direction)
	{
		case ViewDirection::Right:
			m_player.Sprite.setRotation(0);
			break;
		case ViewDirection::Down:
			m_player.Sprite.setRotation(90);
			break;
		case ViewDirection::Left:
			m_player.Sprite.setRotation(180);
			invertY = true;
			break;
		case ViewDirection::Up:
			m_player.Sprite.setRotation(270);
			break;
	}

	m_player.Sprite.setTextureRect(sf::IntRect(m_player.CurrentFrame * m_tileSize.x, (!invertY ? 0 : m_tileSize.y), m_tileSize.x, (!invertY ? m_tileSize.y : -m_tileSize.y)));
	sf::Vector2f playerPosition = sf::Vector2f(m_tileSize.x * (m_player.CurrentCellIndex % m_mapSize.x), m_tileSize.y * floor((m_player.CurrentCellIndex / m_mapSize.x))) +
		m_player.PositionOffset + sf::Vector2f(m_mapScreenOffset) + m_player.Sprite.getOrigin();
	playerPosition = sf::Vector2f(floor(playerPosition.x), floor(playerPosition.y));
	m_player.Sprite.setPosition(playerPosition);
	m_video->draw(m_player.Sprite);

	// Dibujar Fantasmas
	for(unsigned int x = 0; x < m_ghostCount; ++x)
	{
		unsigned int frameStart = 0;

		if(m_ghost[x].IsDead)
		{
			switch(m_ghost[x].Direction)
			{
				case ViewDirection::Right:
					frameStart = 9;
					break;
				case ViewDirection::Down:
					frameStart = 10;
					break;
				case ViewDirection::Left:
					frameStart = 8;
					break;
				case ViewDirection::Up:
					frameStart = 11;
					break;
			}

			m_ghost[x].CurrentFrame = 0;
			m_ghost[x].Sprite.setColor(sf::Color::White);
		}
		else if(m_ghostKillTimer.isStarted() && m_ghost[x].HomeIndex != m_ghost[x].CurrentCellIndex && !m_ghost[x].Invulnerable)
		{
			frameStart = 12;

			if(m_ghostKillTimer.getTicks() > 5000)
			{
				frameStart += (unsigned int)((unsigned int)ceil((m_ghostKillTimer.getTicks() - 2000) / 250) % 2 == 0 ? 2 : 0);
			}

			m_ghost[x].Sprite.setColor(sf::Color::White);
		}
		else
		{
			switch(m_ghost[x].Direction)
			{
				case ViewDirection::Right:
					frameStart = 2;
					break;
				case ViewDirection::Down:
					frameStart = 4;
					break;
				case ViewDirection::Left:
					frameStart = 0;
					break;
				case ViewDirection::Up:
					frameStart = 6;
					break;
			}

			m_ghost[x].Sprite.setColor(m_ghost[x].color);
		}

		m_ghost[x].Sprite.setTextureRect(sf::IntRect(m_ghost[x].CurrentFrame * m_tileSize.x + (frameStart * m_tileSize.x), 0, m_tileSize.x, m_tileSize.y));
		sf::Vector2f ghostPosition = sf::Vector2f(m_tileSize.x * (m_ghost[x].CurrentCellIndex % m_mapSize.x), m_tileSize.y * floor((m_ghost[x].CurrentCellIndex / m_mapSize.x))) +
			m_ghost[x].PositionOffset + sf::Vector2f(m_mapScreenOffset);
		ghostPosition = sf::Vector2f(floor(ghostPosition.x), floor(ghostPosition.y));
		m_ghost[x].Sprite.setPosition(ghostPosition);
		m_video->draw(m_ghost[x].Sprite);
	}

	// Dibujar Texto (Puntuacion, Vidas y Ready)
	char tempString[256];

	if(m_readyTimer.getTicks() > 0)
	{
		m_video->drawRectangle(sf::Vector2f(275, 247), sf::Vector2f(90, 32), sf::Color::Black);

		sprintf(tempString, "READY!");

		sf::Text readyText;

		readyText.setFont(m_textFont);
		readyText.setString(tempString);
		readyText.setCharacterSize(21);
		readyText.setStyle(sf::Text::Bold);
		readyText.setColor(sf::Color::Yellow);
		readyText.setPosition(278,250);
		m_video->draw(readyText);
	}

	sprintf(tempString, "SCORE");

	sf::Text scoreText;
	scoreText.setFont(m_textFont);
	scoreText.setString(tempString);
	scoreText.setCharacterSize(14);
	scoreText.setStyle(sf::Text::Style::Bold);
	scoreText.setColor(sf::Color::White);
	scoreText.setPosition(25,15);
	m_video->draw(scoreText);

	sprintf(tempString, "LIVES");

	scoreText.setString(tempString);
	scoreText.setPosition(565,15);
	m_video->draw(scoreText);

	sprintf(tempString, "%05u", m_gameScore);

	scoreText.setCharacterSize(12);
	scoreText.setString(tempString);
	scoreText.setStyle(sf::Text::Style::Regular);
	scoreText.setPosition(35,32);
	m_video->draw(scoreText);

	for(unsigned int x = 0; x < m_player.Lives; ++x)
	{
		m_liveSprite.setPosition(sf::Vector2f(578, 39 + ((m_tileSize.y + 5) * x)));

		m_video->draw(m_liveSprite);
	}

	m_video->swapBuffers();
}


void Pacman::onEvent(const int eventType, const int param1, const int param2)
{
	m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_KEYDOWN:
			switch (param1)
			{
				case KEY::F2:
					if(m_sound.getVolume() > 0)
					{
						m_sound.setVolume(0);
					}
					else
					{
						m_sound.setVolume(100);
					}
					break;

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
			break;
	}
}


void Pacman::reset()
{
	m_player.Lives = 3;
	m_gameScore = 0;

	resetGame();
}


void Pacman::end()
{
	// Nada
}


void Pacman::resetGame()
{
	if(m_player.Lives == 0)
	{
		reset();
	}

	m_player.DesiredDirection = ViewDirection::Left;
	m_player.Direction = m_player.DesiredDirection;
	m_player.PositionOffset = sf::Vector2f(0, 0);
	m_player.MoveSpeed = 1.5;
	m_player.CurrentFrame = 1;
	m_player.IsDead = false;

	m_ballPosition.clear();
	m_ballBigPosition.clear();

	bool pacmanExists = false;
	unsigned int ghostCount = 0;

	for(int y = 0; y < m_mapSize.y; ++y)
	{
		for(int x = 0; x < m_mapSize.x; ++x)
		{
			unsigned int index = x + (y * m_mapSize.x);

			mapSetCell(index, (CellType)m_mapInfo[index]);

			if(m_mapInfo[index] == CellType::Ball)
			{
				m_ballPosition.push_back(sf::Vector2i(x, y));
			}
			else if(m_mapInfo[index] == CellType::BallBig)
			{
				m_ballBigPosition.push_back(sf::Vector2i(x, y));
			}
			else if(m_mapInfo[index] == CellType::GhostStartPosition)
			{
				if(ghostCount >= 4)
				{
					ghostCount -= 1;
				}

				m_ghost[ghostCount].HomeIndex = index;
				m_ghost[ghostCount].CurrentCellIndex = m_ghost[ghostCount].HomeIndex;

				ghostCount += 1;
			}
			else if(m_mapInfo[index] == CellType::PacmanStartPosition)
			{
				m_player.CurrentCellIndex = index;

				pacmanExists = true;
			}
		}
	}

	m_ghostCount = ghostCount;

	// Si no existe pacman, o no hay ninguna bola, o no existe ningun fantasma...
	if(!pacmanExists || (m_ballPosition.empty() && m_ballBigPosition.empty()) || m_ghostCount == 0)
	{
		stop();

		return;
	}

	for(unsigned int x = 0; x < m_ghostCount; ++x)
	{
		m_ghost[x].MoveSpeed = 1.4;
		m_ghost[x].CurrentFrame = 0;
		m_ghost[x].DesiredDirection = ViewDirection::Left;
		m_ghost[x].Direction = m_ghost[x].DesiredDirection;
		m_ghost[x].PositionOffset = sf::Vector2f(0, 0);
		m_ghost[x].Invulnerable = false;
		m_ghost[x].IsDead = false;
		m_ghost[x].LastCellChecked = m_mapNullCell;
		m_ghost[x].IsInChase = true;
		m_ghost[x].StateDuration = 1000;
		m_ghost[x].LastStateChange = 0;
	}

	m_ghost[0].TimeToRelease = 0;
	m_ghost[1].TimeToRelease = 1000;
	m_ghost[2].TimeToRelease = 4000;
	m_ghost[3].TimeToRelease = 10000;

	m_ghost[0].color = sf::Color::Red;
	m_ghost[1].color = sf::Color::Yellow;
	m_ghost[2].color = sf::Color(75,75,255);
	m_ghost[3].color = sf::Color::Green;

	m_ghostKillTimer.stop();
	m_pauseTimer.stop();
	m_readyTimer.start();
}


bool Pacman::loadMap()
{
	unsigned int counter = 0;
	std::string stringLine;

	std::ifstream fileMap;
	fileMap.open("resources/pacman_map.txt");

	if(!fileMap)
	{
		return false;
	}

	while(getline(fileMap, stringLine))
	{
		for (unsigned int columnChar = 0; columnChar < stringLine.length(); ++columnChar)
		{
			switch(stringLine[columnChar])
			{
				case '0':
					m_mapInfo[counter] = CellType::Nothing;
					counter += 1;
					break;

				case '1':
					m_mapInfo[counter] = CellType::Wall;
					counter += 1;
					break;

				case '2':
					m_mapInfo[counter] = CellType::Ball;
					counter += 1;
					break;

				case '3':
					m_mapInfo[counter] = CellType::BallBig;
					counter += 1;
					break;

				case '4':
					m_mapInfo[counter] = CellType::GhostStartPosition;
					counter += 1;
					break;

				case '5':
					m_mapInfo[counter] = CellType::GhostDoor;
					counter += 1;
					break;

				case '6':
					m_mapInfo[counter] = CellType::PacmanStartPosition;
					counter += 1;
					break;

				default:
					break;
			}
		}
	}

	if(counter != m_mapNullCell)
	{
		return false;
	}

	return true;
}


void Pacman::mapSetCell(unsigned int cellIndex, CellType cellType)
{
	int tileNumber;

	switch(cellType)
	{
		case CellType::Nothing:
			tileNumber = 0;
			break;
		case CellType::Wall:
			tileNumber = 3;
			break;
		case CellType::Ball:
			tileNumber = 1;
			break;
		case CellType::BallBig:
			tileNumber = 2;
			break;
		case CellType::GhostStartPosition:
			tileNumber = 0;
			break;
		case CellType::GhostDoor:
			tileNumber = 4;
			break;
		case CellType::PacmanStartPosition:
			tileNumber = 0;
			break;
		default:
			tileNumber = 0;
			break;
	}

	int texturePosX = tileNumber % (m_mapTileSet.getSize().x / m_tileSize.x);
	int texturePosY = tileNumber / (m_mapTileSet.getSize().x / m_tileSize.x);

	sf::Vertex* quad = &m_mapVertexArray[cellIndex * 4];

	quad[0].texCoords = sf::Vector2f(texturePosX * m_tileSize.x, texturePosY * m_tileSize.y);
	quad[1].texCoords = sf::Vector2f((texturePosX + 1) * m_tileSize.x, texturePosY * m_tileSize.y);
	quad[2].texCoords = sf::Vector2f((texturePosX + 1) * m_tileSize.x, (texturePosY + 1) * m_tileSize.y);
	quad[3].texCoords = sf::Vector2f(texturePosX * m_tileSize.x, (texturePosY + 1) * m_tileSize.y);
}


bool Pacman::checkCollision(unsigned int cellIndex, ViewDirection direction, bool isPlayer)
{
	int mapInfo = getMapInfo(cellIndex, direction);

	if(mapInfo == CellType::Wall || (isPlayer ? mapInfo == CellType::GhostDoor : false))
	{
		return true;
	}

	return false;
}


void Pacman::moveEntity(unsigned int* cellIndex, sf::Vector2f* offset, ViewDirection* direction, ViewDirection* desiredDirection, bool* isMoving, float speed, bool isPlayer)
{
	// Si está quieto, modificamos su dirección directamente
	if(!*isMoving && *direction != *desiredDirection)
	{
		*direction = *desiredDirection;
	}

	*isMoving = true;

	// Modificamos su dirección si es posible y movemos el objeto resolviendo colisiones
	if(*direction == ViewDirection::Left)
	{
		if(*desiredDirection != *direction && !checkCollision(*cellIndex, *desiredDirection, isPlayer))
		{
			switch(*desiredDirection)
			{
				case ViewDirection::Right:
					*direction = *desiredDirection;
					break;
				case ViewDirection::Up:
				case ViewDirection::Down:
					if(offset->x >= 0 && (offset->x + speed) >= 0)
					{
						offset->x = 0;
						*direction = *desiredDirection;

						return;
					}
					break;
				default:
					break;
			}
		}

		if(offset->x <= 0 && checkCollision(*cellIndex, *direction, isPlayer))
		{
			*isMoving = false;
			*desiredDirection = *direction;
			offset->x = 0;

			return;
		}

		offset->x -= speed;

		if(offset->x < -(m_tileSize.x / 2))
		{
			*cellIndex = getMapIndex(*cellIndex, ViewDirection::Left);

			offset->x = (m_tileSize.x / 2) - abs((m_tileSize.x / 2) + offset->x);
		}
	}
	else if(*direction == ViewDirection::Right)
	{
		if(*desiredDirection != *direction && !checkCollision(*cellIndex, *desiredDirection, isPlayer))
		{
			switch(*desiredDirection)
			{
				case ViewDirection::Left:
					*direction = *desiredDirection;
					break;
				case ViewDirection::Up:
				case ViewDirection::Down:
					if(offset->x <= 0 && (offset->x - speed) <= 0)
					{
						offset->x = 0;
						*direction = *desiredDirection;

						return;
					}
					break;
				default:
					break;
			}
		}

		if(offset->x >= 0 && checkCollision(*cellIndex, *direction, isPlayer))
		{
			*isMoving = false;
			*desiredDirection = *direction;
			offset->x = 0;

			return;
		}

		offset->x += speed;

		if(offset->x > (m_tileSize.x / 2))
		{
			*cellIndex = getMapIndex(*cellIndex, ViewDirection::Right);

			offset->x = -(m_tileSize.x / 2) + abs((m_tileSize.x / 2) - offset->x);
		}
	}
	else if(*direction == ViewDirection::Up)
	{
		if(*desiredDirection != *direction && !checkCollision(*cellIndex, *desiredDirection, isPlayer))
		{
			switch(*desiredDirection)
			{
				case ViewDirection::Down:
					*direction = *desiredDirection;
					break;
				case ViewDirection::Left:
				case ViewDirection::Right:
					if(offset->y >= 0 && (offset->y + speed) >= 0)
					{
						offset->y = 0;
						*direction = *desiredDirection;

						return;
					}
					break;
				default:
					break;
			}
		}

		if(offset->y <= 0 && checkCollision(*cellIndex, *direction, isPlayer))
		{
			*isMoving = false;
			*desiredDirection = *direction;
			offset->y = 0;

			return;
		}

		offset->y -= speed;

		if(offset->y < -(m_tileSize.y / 2))
		{
			*cellIndex = getMapIndex(*cellIndex, ViewDirection::Up);

			offset->y = (m_tileSize.y / 2) - abs((m_tileSize.y / 2) + offset->y);
		}
	}
	else if(*direction == ViewDirection::Down)
	{
		if(*desiredDirection != *direction && !checkCollision(*cellIndex, *desiredDirection, isPlayer))
		{
			switch(*desiredDirection)
			{
				case ViewDirection::Up:
					*direction = *desiredDirection;
					break;
				case ViewDirection::Left:
				case ViewDirection::Right:
					if(offset->y <= 0 && (offset->y - speed) <= 0)
					{
						offset->y = 0;
						*direction = *desiredDirection;

						return;
					}
					break;
				default:
					break;
			}
		}

		if(offset->y >= 0 && checkCollision(*cellIndex, *direction, isPlayer))
		{
			*isMoving = false;
			*desiredDirection = *direction;
			offset->y = 0;

			return;
		}

		offset->y += speed;

		if(offset->y > (m_tileSize.y / 2))
		{
			*cellIndex = getMapIndex(*cellIndex, ViewDirection::Down);

			offset->y = -(m_tileSize.y / 2) + abs((m_tileSize.y / 2) - offset->y);
		}
	}
}


Pacman::ViewDirection Pacman::getNextDirection(unsigned int startIndex, unsigned int searchIndex, unsigned int ignoreCell)
{
	std::list<Node> OpenNodeList;
	std::list<Node> ClosedNodeList;

	// Guardamos en la lista de Nodos Abiertos el Nodo correspondiente a startIndex
	OpenNodeList.push_back(Node());
	OpenNodeList.back().Index = startIndex;
	OpenNodeList.back().Range = abs((startIndex % m_mapSize.x) - (searchIndex % m_mapSize.x)) + abs(floor(startIndex / m_mapSize.y) - floor(searchIndex / m_mapSize.y));

	if(ignoreCell == m_mapNullCell)
	{
		// Guardamos en la lista de Nodos Cerrados el Nodo correspondiente a la casilla a ignorar
		ClosedNodeList.push_back(Node());
		ClosedNodeList.back().Index = ignoreCell;
	}

	Node* preferentNode = &OpenNodeList.back();

	// Hasta que no encuentre el destino o la lista de nodos abiertos se vacíe (no haya caminos posibles)...
	while (preferentNode->Index != searchIndex && !OpenNodeList.empty())
	{
		// Si el nodo preferente está en la lista de nodos cerrados...
		for (auto closedNode : ClosedNodeList)
		{
			if (closedNode.Index == preferentNode->Index)
			{
				preferentNode = &OpenNodeList.back();

				// Elegimos el primer nodo más preferente de la lista de nodos abiertos
				for (auto openNodeIt = OpenNodeList.begin(); openNodeIt != OpenNodeList.end(); ++openNodeIt)
				//for (auto openNode : OpenNodeList)
				{
					if ((preferentNode->Range + preferentNode->Cost) > (openNodeIt->Range + openNodeIt->Cost))
					{
						preferentNode = &*openNodeIt;
					}
				}

				break;
			}
		}

		// Guardamos el nodo preferente en la lista de Nodos cerrados y lo eliminamos de la lista de nodos abiertos
		for (auto openNodeIt = OpenNodeList.begin(); openNodeIt != OpenNodeList.end(); ++openNodeIt)
		{
			if (openNodeIt->Index == preferentNode->Index)
			{
				ClosedNodeList.push_back(*preferentNode);

				// Actualizamos los punteros
				for (Node openNode : OpenNodeList)
				{
					if(openNode.ParentNode == preferentNode)
					{
						openNode.ParentNode = &ClosedNodeList.back();
					}
				}

				preferentNode = &ClosedNodeList.back();

				OpenNodeList.erase(openNodeIt);

				break;
			}
		}

		std::vector<unsigned int> nextIndex;

		// Añadimos a nextIndex CADA UNA de las 4 direcciones si es posible su tránsito
		if (!checkCollision(preferentNode->Index, ViewDirection::Left, false))
		{
			nextIndex.push_back(getMapIndex(preferentNode->Index, ViewDirection::Left));
		}
		if (!checkCollision(preferentNode->Index, ViewDirection::Right, false))
		{
			nextIndex.push_back(getMapIndex(preferentNode->Index, ViewDirection::Right));
		}
		if (!checkCollision(preferentNode->Index, ViewDirection::Up, false))
		{
			nextIndex.push_back(getMapIndex(preferentNode->Index, ViewDirection::Up));
		}
		if (!checkCollision(preferentNode->Index, ViewDirection::Down, false))
		{
			nextIndex.push_back(getMapIndex(preferentNode->Index, ViewDirection::Down));
		}

		if (!nextIndex.empty())
		{
			Node* previousNode = preferentNode;

			for (unsigned int Index : nextIndex)
			{
				bool isValid = true;

				// Miramos si existe en la lista de nodos abiertos
				for (Node openNode : OpenNodeList)
				{
					if (openNode.Index == Index)
					{
						isValid = false;

						break;
					}
				}

				if (!isValid)
				{
					continue;
				}

				// Miramos si existe en la lista de nodos cerrados
				for (Node closedNode : ClosedNodeList)
				{
					if (closedNode.Index == Index)
					{
						isValid = false;

						break;
					}
				}

				if (!isValid)
				{
					continue;
				}

				// Si NO existe en ninguna de las listas anteriores, añadimos el nodo a la lista de nodos abiertos
				OpenNodeList.push_back(Node());
				OpenNodeList.back().Index = Index;
				OpenNodeList.back().ParentNode = previousNode;
				OpenNodeList.back().Cost = (previousNode->Cost + 1);
				OpenNodeList.back().Range = abs((int)(Index % m_mapSize.x) - (int)(searchIndex % m_mapSize.x)) + abs(floor(Index / m_mapSize.y) - floor(searchIndex / m_mapSize.y));

				// ... y actualizamos preferentNode si así fuera el caso
				if ((preferentNode->Range + preferentNode->Cost) > (OpenNodeList.back().Range + OpenNodeList.back().Cost))
				{
					preferentNode = &OpenNodeList.back();
				}
			}
		}
	}

	// Si el ultimo nodo preferente encontró el destino...
	if (preferentNode->Index == searchIndex)
	{
		// Localizamos el nodo con la siguiente casilla a desplazarse desde el nodo destino
		while (preferentNode->ParentNode->Index != startIndex)
		{
			preferentNode = preferentNode->ParentNode;
		}

		// Nos movemos en una dirección segun el nodo posterior al nodo origen
		if (preferentNode->Index == (startIndex - 1))
		{
			return ViewDirection::Left;
		}
		else if (preferentNode->Index == (startIndex + 1))
		{
			return ViewDirection::Right;
		}
		else if (preferentNode->Index == (startIndex + m_mapSize.x))
		{
			return ViewDirection::Down;
		}
		else
		{
			return ViewDirection::Up;
		}
	}
	else
	{
		return getRandomDirection(startIndex, ignoreCell);
	}
}


Pacman::ViewDirection Pacman::getRandomDirection(unsigned int cellIndex, unsigned int ignoreCell)
{
	std::vector<ViewDirection> randomDirection;
	ViewDirection ignoreDirection = ViewDirection::Up; // Inicializamos su valor para que no se queje el compilador

	if(ignoreCell != m_mapNullCell)
	{
		if(ignoreCell == getMapIndex(cellIndex, ViewDirection::Right))
		{
			ignoreDirection = ViewDirection::Right;
		}
		else if(ignoreCell == getMapIndex(cellIndex, ViewDirection::Left))
		{
			ignoreDirection = ViewDirection::Left;
		}
		else if(ignoreCell == getMapIndex(cellIndex, ViewDirection::Down))
		{
			ignoreDirection = ViewDirection::Down;
		}
		else
		{
			ignoreDirection = ViewDirection::Up;
		}

		if(getMapInfo(cellIndex, ViewDirection::Right) != CellType::Wall)
		{
			if(ignoreDirection != ViewDirection::Right)
			{
				randomDirection.push_back(ViewDirection::Right);
			}
		}

		if(getMapInfo(cellIndex, ViewDirection::Left) != CellType::Wall)
		{
			if(ignoreDirection != ViewDirection::Left)
			{
				randomDirection.push_back(ViewDirection::Left);
			}
		}

		if(getMapInfo(cellIndex, ViewDirection::Up) != CellType::Wall)
		{
			if(ignoreDirection != ViewDirection::Up)
			{
				randomDirection.push_back(ViewDirection::Up);
			}
		}

		if(getMapInfo(cellIndex, ViewDirection::Down) != CellType::Wall)
		{
			if(ignoreDirection != ViewDirection::Down)
			{
				randomDirection.push_back(ViewDirection::Down);
			}
		}
	}
	else
	{
		if(getMapInfo(cellIndex, ViewDirection::Right) != CellType::Wall)
		{
			randomDirection.push_back(ViewDirection::Right);
		}

		if(getMapInfo(cellIndex, ViewDirection::Left) != CellType::Wall)
		{
			randomDirection.push_back(ViewDirection::Left);
		}

		if(getMapInfo(cellIndex, ViewDirection::Up) != CellType::Wall)
		{
			randomDirection.push_back(ViewDirection::Up);
		}

		if(getMapInfo(cellIndex, ViewDirection::Down) != CellType::Wall)
		{
			randomDirection.push_back(ViewDirection::Down);
		}
	}

	if(randomDirection.empty())
	{
		return ignoreDirection;
	}
	else
	{
		return randomDirection[rand() % randomDirection.size()];
	}
}


unsigned int Pacman::getMapIndex(unsigned int cellIndex, ViewDirection direction)
{
	unsigned int cellMapIndex;

	if(direction == ViewDirection::Left)
	{
		if(cellIndex % m_mapSize.x == 0)
		{
			cellMapIndex = cellIndex + (m_mapSize.x - 1);
		}
		else
		{
			cellMapIndex = cellIndex - 1;
		}
	}
	else if(direction == ViewDirection::Right)
	{
		if(cellIndex % m_mapSize.x == (unsigned int)(m_mapSize.x - 1))
		{
			cellMapIndex = cellIndex - (m_mapSize.x - 1);
		}
		else
		{
			cellMapIndex = cellIndex + 1;
		}
	}
	else if(direction == ViewDirection::Up)
	{
		if(floor(cellIndex / m_mapSize.x) == 0)
		{
			cellMapIndex = (m_mapSize.x * m_mapSize.y) - (m_mapSize.x - cellIndex);
		}
		else
		{
			cellMapIndex = cellIndex - m_mapSize.x;
		}
	}
	else
	{
		if(floor(cellIndex / m_mapSize.x) == (m_mapSize.y - 1))
		{
			cellMapIndex = abs((cellIndex + m_mapSize.x) - (m_mapSize.x * m_mapSize.y));
		}
		else
		{
			cellMapIndex = cellIndex + m_mapSize.x;
		}
	}

	return cellMapIndex;
}


unsigned int Pacman::getMapInfo(unsigned int cellIndex, ViewDirection direction)
{
	return m_mapInfo[getMapIndex(cellIndex, direction)];
}


void Pacman::ghostCollide(unsigned int ghostId)
{
	if(m_ghostKillTimer.isStarted() && !m_ghost[ghostId].Invulnerable)
	{
		m_ghost[ghostId].IsDead = true;
		m_ghost[ghostId].Direction = getNextDirection(m_ghost[ghostId].CurrentCellIndex, m_ghost[ghostId].HomeIndex, m_mapNullCell);

		unsigned int scoreEarned = 0;

		if(m_powerupKillCounter == 3)
		{
			scoreEarned = 1600;
		}
		else if(m_powerupKillCounter == 2)
		{
			scoreEarned = 800;
		}
		else if(m_powerupKillCounter == 1)
		{
			scoreEarned = 400;
		}
		else
		{
			scoreEarned = 200;
		}

		addScore(scoreEarned);

		if(m_powerupKillCounter < m_ghostCount)
		{
			m_powerupKillCounter += 1;
		}

		m_sound.setBuffer(m_killSound);
		m_sound.play();
	}
	else
	{
		m_player.Lives -= 1;
		m_player.IsDead = true;

		m_sound.setBuffer(m_deadSound);
		m_sound.play();
	}

	m_pauseTimer.start();
	m_gameTimer.pause();
	m_frameTimer.pause();
	if(m_ghostKillTimer.isStarted())
	{
		m_ghostKillTimer.pause();
	}
}


void Pacman::addScore(unsigned int score)
{
	// Cada 10000 puntos le damos una vida al jugador (Máx 5)
	if(m_player.Lives < 5 && ((m_gameScore % 10000) + score) >= 10000)
	{
		m_player.Lives += 1;
	}

	m_gameScore += score;
}
