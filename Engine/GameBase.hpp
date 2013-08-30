#pragma once
#ifndef GAME_BASE_HPP
#define GAME_BASE_HPP


#include "helpers/Event.hpp"
#include "input/Input.hpp"
class Timer;
class IVideo;
class IDebug;


class GameBase
{
	public:
		GameBase(unsigned int sizeX = 1024, unsigned int sizeY = 768); // Por defecto
		~GameBase();
		void start();
		void stop();
		unsigned int getTimeRunning();
		unsigned int getTickCount();
		unsigned int getFps();
		unsigned int getMsLastFrame();

    protected:
		Input* m_input;
		IVideo* m_video;
		IDebug* m_debug;

	private:
		void delayMs(const unsigned int delayMs);
		void loop();
		void systemInit();
		void systemEnd();
		virtual void init() = 0;
		virtual void onTick() = 0;
		virtual void onRender() = 0;
		virtual void onEvent(const int eventType, const int param1, const int param2) = 0;
		virtual void end() = 0;

		EventListener3<GameBase, void, int, int, int> m_eventListener;
		bool m_run;
		unsigned int m_fpsCounter;
		Timer* m_fpsTimer;
		Timer* m_updateTimer;
		Timer* m_runningTimer;
		unsigned int m_tickCount;
		unsigned int m_fps;
		unsigned int m_msLastFrame;
};


#endif // GAME_BASE_HPP
