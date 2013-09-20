#include "GameBase.hpp"
#include "Defines.hpp"
#include "input/Input.hpp"
#include "video/Video.hpp"
#include "helpers/Timer.hpp"


GameBase::GameBase()
{
	srand(time(NULL));

	m_debug = DebugPtr(new Debug());
	m_video = VideoPtr(new Video());
	m_input = InputPtr(new Input());

	m_run = true;
}


void GameBase::start()
{
	if(m_video->init())
	{
		loop();
	}
}


void GameBase::stop()
{
	m_run = false;
}


unsigned int GameBase::getTimeRunning()
{
	return m_runningTimer.getTicks();
}


unsigned int GameBase::getFps()
{
	return m_fps;
}


void GameBase::delayMs(const unsigned int delayMs)
{
	sf::sleep(sf::milliseconds(delayMs));
}


void GameBase::loop()
{
	systemInit();

	while (m_run)
	{
		m_fpsTimer.start();

		m_input->onTick(m_video->getWindow());
		onTick();
		onRender();

		if (m_updateTimer.getTicks() >= 1000)
		{
			m_fps = m_fpsCounter;
			m_fpsCounter = 0;
			m_updateTimer.start();
		}

		++m_fpsCounter;

		m_msFrameDuration = ceil(1000.0 / m_video->getFpsLimit());

		if (m_fpsTimer.getTicks() < m_msFrameDuration)
		{
			delayMs(m_msFrameDuration - m_fpsTimer.getTicks());
		}
	}

	systemEnd();
}


void GameBase::systemInit()
{
	m_fpsCounter = 0;
	m_fps = m_video->getFpsLimit();

	init();

	m_runningTimer.start();
	m_updateTimer.start();
}


void GameBase::systemEnd()
{
	end();

	m_updateTimer.stop();
	m_fpsTimer.stop();
	m_runningTimer.stop();
}
