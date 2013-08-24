#include "PongController.hpp"


Pong::Pong() : GameBase(1024, 768)
{
	m_fuente.loadFromFile("resources/Arial.ttf");
	m_marcador.setFont(m_fuente);
	m_marcador.setCharacterSize(50);
	m_marcador.setStyle(sf::Text::Regular);
	m_marcador.setColor(sf::Color::White);

	reset();
}


Pong::~Pong()
{

}


void Pong::init()
{

}


void Pong::onTick()
{
	// Movimiento Jugador
	if (INPUT->getKeyHeld()->Up.value)
	{
		if (m_playerPos.y > 0)
		{
			m_playerPos.y -= 4;
		}
	}

	if (INPUT->getKeyHeld()->Down.value)
	{
		if (m_playerPos.y <= 668)
		{
			m_playerPos.y += 4;
		}
	}

	// Movimiento CPU
	if (m_ballPos.y + 10 < m_cpuPos.y + 50)
	{
		if (m_cpuPos.y > 0)
		{
			m_cpuPos.y -= 4 + (0.5 * (signed int)(m_playerScore - m_cpuScore));
		}
	}
	else
	{
		if (m_cpuPos.y <= 668)
		{
			m_cpuPos.y += 4 + (0.5 * (signed int)(m_playerScore - m_cpuScore));
		}
	}

	// Colisiones Palas-Pelota
	if (m_ballPos.x <= m_playerPos.x + 20 && m_ballPos.x + 20 >= m_playerPos.x)
	{
		if (m_ballPos.y + 20 >= m_playerPos.y && m_ballPos.y <= m_playerPos.y + 100)
		{
			m_ballMov.x = 1;
		}
	}

	if (m_ballPos.x <= m_cpuPos.x + 20 && m_ballPos.x + 20 >= m_cpuPos.x)
	{
		if (m_ballPos.y + 20 >= m_cpuPos.y && m_ballPos.y <= m_cpuPos.y + 100)
		{
			m_ballMov.x = 0;
		}
	}

	// Colisiones Bordes Pelota
	if (m_ballPos.x - 5 < 0)
	{
		m_cpuScore++;
		m_playerPos.y = 334;
		m_cpuPos.y = 334;
		m_ballMov.x = 1;
		m_ballPos.x = 502;
		m_ballPos.y = 374;
	}

	if (m_ballPos.x + 5 > 1004)
	{
		m_playerScore++;
		m_playerPos.y = 334;
		m_cpuPos.y = 334;
		m_ballMov.x = 0;
		m_ballPos.x = 502;
		m_ballPos.y = 374;
	}

	if (m_ballPos.y - 5 < 0)
	{
		m_ballMov.y = 1;
	}

	if (m_ballPos.y + 5 > 748)
	{
		m_ballMov.y = 0;
	}

	// Movimiento Pelota
	if (m_ballMov.x)
	{
		m_ballPos.x += 5 + (0.5 * (signed int)(m_playerScore - m_cpuScore));
	}
	else
	{
		m_ballPos.x -= 5 + (0.5 * (signed int)(m_playerScore - m_cpuScore));
	}

	if (m_ballMov.y)
	{
		m_ballPos.y += 5 + (0.5 * (signed int)(m_playerScore - m_cpuScore));
	}
	else
	{
		m_ballPos.y -= 5 + (0.5 * (signed int)(m_playerScore - m_cpuScore));
	}
}


void Pong::onRender()
{
	sf::RenderWindow* window = VIDEO->getWindow();
	window->clear(sf::Color::Black);

	char message[50];
	std::sprintf(message, "%02d | %02d", m_playerScore, m_cpuScore);
	m_marcador.setString(message);
	m_marcador.setPosition(450, 20);
	window->draw(m_marcador);

	VIDEO->drawRectangle(Vector2f(m_ballPos.x, m_ballPos.y), Vector2f(20, 20), sf::Color::White);
	VIDEO->drawRectangle(Vector2f(m_playerPos.x, m_playerPos.y), Vector2f(20, 100), sf::Color::White);
	VIDEO->drawRectangle(Vector2f(m_cpuPos.x, m_cpuPos.y), Vector2f(20, 100), sf::Color::White);

	VIDEO->swapBuffers();
}


void Pong::onEvent(const int eventType, const int param1, const int param2)
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


void Pong::reset()
{
	m_ballPos.x = 502;
	m_ballPos.y = 374;
	m_ballMov.x = 1;
	m_ballMov.y = 1;
	m_playerPos.x = 10;
	m_playerPos.y = 334;
	m_cpuPos.x = 1024 - 30;
	m_cpuPos.y = 334;
	m_playerScore = 0;
	m_cpuScore = 0;
}


void Pong::end()
{

}
