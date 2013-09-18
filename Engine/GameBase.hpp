#pragma once
#ifndef GAME_BASE_HPP
#define GAME_BASE_HPP


#include "helpers/Event.hpp"
#include "helpers/Timer.hpp"
#include "input/Input.hpp"
#include "video/Video.hpp"
#include "debug/DebugLog.hpp"


class GameBase
{
	public:
		GameBase();
		~GameBase() {};
		void start();
		void stop();
		unsigned int getTimeRunning();
		unsigned int getFps();

	protected:
		InputPtr m_input;
		VideoPtr m_video;
		DebugPtr m_debug;

	private:
		void delayMs(const unsigned int delayMs);
		void loop();
		void systemInit();
		void systemEnd();
		virtual void init() {};
		virtual void onTick() = 0;
		virtual void onRender() = 0;
		virtual void end() {};

		bool m_run;
		unsigned int m_fpsCounter;
		unsigned int m_msFrameDuration;
		Timer m_fpsTimer;
		Timer m_updateTimer;
		Timer m_runningTimer;
		unsigned int m_fps;
};


#endif // GAME_BASE_HPP
