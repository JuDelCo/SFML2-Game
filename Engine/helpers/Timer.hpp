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
		void Start();
		void Pause();
		void Continue();
		void Stop();
		bool is_started();
		bool is_paused();
		unsigned int get_ticks();

	private:
		sf::Clock* clock_;
		unsigned int start_ticks_;
		unsigned int paused_ticks_;
		bool paused_;
		bool started_;
};


#endif // TIMER_HPP
