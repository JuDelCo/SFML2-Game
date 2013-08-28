#pragma once
#ifndef TIMER_HPP
#define TIMER_HPP


namespace sf
{
	class Clock;
}


class Timer
{
	public:
		Timer();
		~Timer();
		void start();
		void pause();
		void resume();
		void stop();
		bool isStarted();
		bool isPaused();
		unsigned int getTicks();

	private:
		sf::Clock* m_clock;
		unsigned int m_startTicks;
		unsigned int m_pausedTicks;
		bool m_paused;
		bool m_started;
};


#endif // TIMER_HPP
