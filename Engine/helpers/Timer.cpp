// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Timer.hpp"
#include <SFML/system.hpp>

#define getElapsedTimeMs() getElapsedTime().asMilliseconds()

Timer::Timer()
{
	m_clock = ClockPtr(new sf::Clock());

	m_started = false;
	m_paused = false;

	m_startTicks = 0;
	m_pausedTicks = 0;
}

void Timer::start()
{
	if (!isStarted())
	{
		m_started = true;
		m_paused = false;
	}

	reset();
}

void Timer::reset()
{
	if(isStarted())
	{
		m_startTicks = m_clock->getElapsedTimeMs() - m_pausedTicks;
	}
}

void Timer::pause()
{
	if (isStarted() && !isPaused())
	{
		m_paused = true;
		m_pausedTicks = m_clock->getElapsedTimeMs() - m_startTicks;
	}
}

void Timer::resume()
{
	if (isPaused())
	{
		m_paused = false;

		reset();
	}
}

void Timer::stop()
{
	if(isStarted())
	{
		m_started = false;
		m_paused = false;
	}
}

unsigned int Timer::getTicks()
{
	if (isStarted())
	{
		if (isPaused())
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
