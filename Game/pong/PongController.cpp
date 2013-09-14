#include "PongController.hpp"
#include <stdlib.h>


inline bool check2dCollision(sf::Vector2f pos1, sf::Vector2f size1, sf::Vector2f pos2, sf::Vector2f size2)
{
	return (pos1.x <= (pos2.x + size2.x) && (pos1.x + size1.x) >= pos2.x && pos1.y <= (pos2.y + size2.y) && (pos1.y + size1.y) >= pos2.y ? true : false);
}


Pong::Pong() : GameBase(640, 480)
{
	if (!m_scoreFont.loadFromFile("resources/arial.ttf"))
	{
		stop();
	}

	if (!m_pingSound.loadFromFile("resources/ping.wav"))
	{
		stop();
	}

	if (!m_pongSound.loadFromFile("resources/pong.wav"))
	{
		stop();
	}

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
	if(m_input->getKeyHeld()->Up.value)
	{
		m_playerPosition.y -= 2.5;

		if(m_playerPosition.y < 0)
		{
			m_playerPosition.y = 0;
		}
	}
	else if(m_input->getKeyHeld()->Down.value)
	{
		m_playerPosition.y += 2.5;

		if(m_playerPosition.y + m_playerSize.y > m_screenSize.y)
		{
			m_playerPosition.y = m_screenSize.y - m_playerSize.y;
		}
	}

	if((m_cpuPosition.y + m_cpuSize.y / 2) - 5 > m_ballPosition.y + m_ballSize.y / 2)
	{
		m_cpuPosition.y -= 3;

		if(m_cpuPosition.y < 0)
		{
			m_cpuPosition.y = 0;
		}
	}
	else if((m_cpuPosition.y + m_cpuSize.y / 2) + 5 < m_ballPosition.y + m_ballSize.y / 2)
	{
		m_cpuPosition.y += 3;

		if(m_cpuPosition.y + m_cpuSize.y > m_screenSize.y)
		{
			m_cpuPosition.y = m_screenSize.y - m_cpuSize.y;
		}
	}

	if(check2dCollision(m_ballPosition, m_ballSize, m_playerPosition, m_playerSize))
	{
		m_ballVelocity.x *= -1;

		if(m_ballVelocity.x < 7)
		{
			m_ballVelocity.x += 0.2;
		}

		float diff = (m_ballPosition.y + (m_ballSize.y / 2)) - (m_playerPosition.y + (m_playerSize.y / 2));

		m_ballVelocity.y = (diff / (m_playerSize.y / 2) * 3);

		m_sound.setBuffer(m_pingSound);
		m_sound.play();
	}

	if(check2dCollision(m_ballPosition, m_ballSize, m_cpuPosition, m_cpuSize))
	{
		m_ballVelocity.x *= -1;

		if(m_ballVelocity.x > -7)
		{
			m_ballVelocity.x -= 0.2;
		}

		float diff = (m_ballPosition.y + (m_ballSize.y / 2)) - (m_cpuPosition.y + (m_cpuSize.y / 2));

		m_ballVelocity.y = (diff / (m_cpuSize.y / 2) * 3);

		m_sound.setBuffer(m_pongSound);
		m_sound.play();
	}

	if(m_ballPosition.y < 0)
	{
		m_ballVelocity.y *= -1;
	}
	else if(m_ballPosition.y + m_ballSize.y > m_screenSize.y)
	{
		m_ballVelocity.y *= -1;
	}

	if(m_ballPosition.x < 5)
	{
		m_cpuScore++;
		m_ballVelocity = sf::Vector2f(4, 0);
		m_playerPosition = sf::Vector2f(10, m_screenSize.y / 2 - m_playerSize.y / 2);
		m_cpuPosition = sf::Vector2f(620, m_screenSize.y / 2 - m_cpuSize.y / 2);
		m_ballPosition = sf::Vector2f(m_screenSize.x / 2 - m_ballSize.x / 2, m_screenSize.y / 2 - m_ballSize.y / 2);
	}

	if(m_ballPosition.x > m_screenSize.x - 5)
	{
		m_playerScore++;
		m_ballVelocity = sf::Vector2f(-4, 0);
		m_playerPosition = sf::Vector2f(10, m_screenSize.y / 2 - m_playerSize.y / 2);
		m_cpuPosition = sf::Vector2f(620, m_screenSize.y / 2 - m_cpuSize.y / 2);
		m_ballPosition = sf::Vector2f(m_screenSize.x / 2 - m_ballSize.x / 2, m_screenSize.y / 2 - m_ballSize.y / 2);
	}

	m_ballPosition += m_ballVelocity;
}


void Pong::onRender()
{
	m_video->clear(sf::Color::Black);

	m_video->drawRectangle(m_playerPosition, m_playerSize, sf::Color::White);
	m_video->drawRectangle(m_cpuPosition, m_cpuSize, sf::Color::White);
	m_video->drawRectangle(m_ballPosition, m_ballSize, sf::Color::White);

	char temp[256];
	sprintf(temp, "%i - %i", m_playerScore, m_cpuScore);

	sf::Text score;
	score.setFont(m_scoreFont);
	score.setString(temp);
	score.setCharacterSize(24);
	score.setColor(sf::Color::White);
	score.setPosition(m_screenSize.x / 2 - 25, 5);
	m_video->draw(score);

	m_video->swapBuffers();
}


void Pong::onEvent(const int eventType, const int param1, const int param2)
{
	m_eventHandler.trigger(eventType);

	switch (eventType)
	{
		case EVENT_KEYDOWN:
			switch (param1)
			{
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


void Pong::reset()
{
	m_screenSize = sf::Vector2i(640, 480);

	m_ballSize = sf::Vector2f(10, 10);
	m_ballPosition = sf::Vector2f(m_screenSize.x / 2 - m_ballSize.x / 2, m_screenSize.y / 2 - m_ballSize.y / 2);
	m_ballVelocity = sf::Vector2f(-4, 0);

	m_playerSize = sf::Vector2f(10, 50);
	m_playerPosition = sf::Vector2f(10, m_screenSize.y / 2 - m_playerSize.y / 2);
	m_playerScore = 0;

	m_cpuSize = sf::Vector2f(10, 50);
	m_cpuPosition = sf::Vector2f(620, m_screenSize.y / 2 - m_cpuSize.y / 2);
	m_cpuScore = 0;
}


void Pong::end()
{

}
