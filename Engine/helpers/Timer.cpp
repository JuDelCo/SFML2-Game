#include "Timer.hpp"
#include <SFML/system.hpp>


#define getElapsedTimeMs() getElapsedTime().asMilliseconds()


Timer::Timer()
{
	m_clock = ClockPtr(new sf::Clock());

	m_startTicks = 0;
	m_pausedTicks = 0;
	m_paused = false;
	m_started = false;
}


void Timer::start()
{
	m_started = true;
	m_paused = false;
	m_startTicks = m_clock->getElapsedTimeMs();
}


void Timer::pause()
{
	if ((m_started == true) && (m_paused == false))
	{
		m_paused = true;
		m_pausedTicks = m_clock->getElapsedTimeMs() - m_startTicks;
	}
}


void Timer::resume()
{
	if (m_paused == true)
	{
		m_paused = false;
		m_startTicks = m_clock->getElapsedTimeMs() - m_pausedTicks;
		m_pausedTicks = 0;
	}
}


void Timer::stop()
{
	m_started = false;
	m_paused = false;
}


unsigned int Timer::getTicks()
{
	if (m_started == true)
	{
		if (m_paused == true)
		{
			return m_pausedTicks;
		}
		else
		{
			return m_clock->getElapsedTimeMs() - m_startTicks;
		}
	}

	return 0;
}


bool Timer::isStarted()
{
	return m_started;
}


bool Timer::isPaused()
{
	return m_paused;
}
