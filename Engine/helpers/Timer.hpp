#pragma once
#ifndef TIMER_HPP
#define TIMER_HPP

#include <memory>


namespace sf
{
	class Clock;
}

typedef std::shared_ptr<sf::Clock> ClockPtr;


class Timer
{
	public:
		Timer();
		~Timer() {};
		void start();
		void pause();
		void resume();
		void stop();
		bool isStarted();
		bool isPaused();
		unsigned int getTicks();

	private:
		ClockPtr m_clock;
		unsigned int m_startTicks;
		unsigned int m_pausedTicks;
		bool m_paused;
		bool m_started;
};


#endif // TIMER_HPP
