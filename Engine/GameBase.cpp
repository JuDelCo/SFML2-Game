#include "GameBase.hpp"
#include "Defines.hpp"
#include "debug/DebugLog.hpp"
#include "input/Input.hpp"
#include "video/Video.hpp"
#include "helpers/Timer.hpp"


GameBase::GameBase(unsigned int sizeX, unsigned int sizeY) : m_eventListener(this, &GameBase::onEvent)
{
	srand(time(NULL));

	m_debug = new Debug();
	m_video = new Video(sizeX, sizeY);
	m_input = new Input();
	m_input->m_eventHandler.add(&m_eventListener);

	m_runningTimer = new Timer();
	m_fpsTimer = new Timer();
	m_updateTimer = new Timer();

	m_run = true;
}


GameBase::~GameBase()
{
	delete m_input;
	delete m_video;
	delete m_debug;

	delete m_runningTimer;
	delete m_fpsTimer;
	delete m_updateTimer;
}


void GameBase::start()
{
	loop();
}


void GameBase::stop()
{
	m_run = false;
}


unsigned int GameBase::getTimeRunning()
{
	return m_runningTimer->getTicks();
}


unsigned int GameBase::getTickCount()
{
	return m_tickCount;
}


unsigned int GameBase::getFps()
{
	return m_fps;
}


unsigned int GameBase::getMsLastFrame()
{
	return m_msLastFrame;
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
		m_msLastFrame = m_fpsTimer->getTicks();

		if (m_msLastFrame > 1000.0f / m_video->getFpsLimit())
		{
			m_msLastFrame = (int)(1000.0f / m_video->getFpsLimit());
		}

		m_fpsTimer->start();

		m_input->onTick(m_video->getWindow());
		onTick();
		++m_tickCount;

		onRender();

		if (m_updateTimer->getTicks() >= 1000)
		{
			m_fps = m_fpsCounter;
			m_fpsCounter = 0;
			m_updateTimer->start();
		}

		++m_fpsCounter;

		if (m_fpsTimer->getTicks() < 17)  //59fps
		{
			delayMs(17 - m_fpsTimer->getTicks());
		}
	}

	systemEnd();
}


void GameBase::systemInit()
{
	m_fpsCounter = 0;
	m_fps = m_video->getFpsLimit();
	m_msLastFrame = 0;

	init();

	m_runningTimer->start();
	m_updateTimer->start();
}


void GameBase::systemEnd()
{
	end();

	m_updateTimer->stop();
	m_fpsTimer->stop();
	m_runningTimer->stop();
}
