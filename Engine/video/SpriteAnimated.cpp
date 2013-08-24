#include "SpriteAnimated.hpp"
#include "../ServiceProvider.hpp"
#include "../debug/DebugLog.hpp"
#include "../Defines.hpp"


SpriteAnimated::SpriteAnimated()
{
	m_currentFrame = 0;
	m_numFrames = 1;
	m_frameWidth = 0;
	m_frameTime = 0;
	m_timeRemain = m_frameTime;
}


SpriteAnimated::SpriteAnimated(const std::string location, const int numFrames, const int delay)
{
	loadTexture(location, numFrames);

	m_currentFrame = 0;
	m_frameTime = delay;
	m_timeRemain = m_frameTime;

	setTextureRect(sf::IntRect(0, 0, m_frameWidth, getTexture()->getSize().y));
}


SpriteAnimated::~SpriteAnimated()
{
}


void SpriteAnimated::loadTexture(const std::string location, const int numFrames)
{
	if (!m_image.loadFromFile(location))
	{
		DEBUG->write(LOG_FILE, "Unable to load sprite from: %s", location.c_str());
		exit(ERROR_SPRITELOAD);
	}

	setTexture(m_image);

	m_numFrames = numFrames;
	m_frameWidth = getTexture()->getSize().x / m_numFrames;

	setTextureRect(sf::IntRect(0, 0, m_frameWidth, getTexture()->getSize().y));
}


void SpriteAnimated::update(const int& msLastFrame)
{
	if (m_frameTime > 0)
	{
		m_timeRemain -= msLastFrame; // Revisar si hubiera problema al congelar la pantalla (moverla)

		if (m_timeRemain <= 0)
		{
			if (++m_currentFrame > (m_numFrames - 1))
			{
				m_currentFrame = 0;
			}

			m_timeRemain = m_frameTime;
		}

		setTextureRect(sf::IntRect((m_currentFrame * m_frameWidth), 0, m_frameWidth, getTexture()->getSize().y));
	}
}


int SpriteAnimated::getCurrentFrame()
{
	return m_currentFrame;
}


int SpriteAnimated::getFrameWidth()
{
	return m_frameWidth;
}


int SpriteAnimated::getNumOfFrames()
{
	return m_numFrames;
}


int SpriteAnimated::getDelay()
{
	return m_frameTime;
}


void SpriteAnimated::setCurrentFrame(const int currentFrame)
{
	m_currentFrame = currentFrame;

	setTextureRect(sf::IntRect((m_currentFrame * m_frameWidth), 0, m_frameWidth, getTexture()->getSize().y));
}


void SpriteAnimated::setFrameWidth(const int frameWidth)
{
	m_frameWidth = frameWidth;
}


void SpriteAnimated::setNumOfFrames(const int numFrames)
{
	m_numFrames = numFrames;
}


void SpriteAnimated::setDelay(const int delay)
{
	m_frameTime = delay;
}
