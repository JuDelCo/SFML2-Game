#ifndef GAME_BASE_HPP
#define GAME_BASE_HPP


#include "helpers/Event.hpp"
class Timer;


class GameBase
{
	public:
		GameBase(unsigned int size_x = 1024, unsigned int size_y = 768);
		~GameBase();
		void Start();
		void Stop();
		unsigned int get_time_running();
		unsigned int get_tick_count();
		unsigned int get_fps();
		unsigned int get_milliseconds_last_frame();

	private:
		void DelayMilliseconds(const unsigned int delay_milliseconds);
		void Loop();
		void SystemInit();
		void SystemEnd();
		virtual void Init() = 0;
		virtual void OnTick() = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(const int event_type, const int param_1, const int param_2) = 0;
		virtual void End() = 0;
		EventListener3<GameBase, void, int, int, int> event_listener_;
		bool run_;
		unsigned int fps_counter_;
		Timer* fps_timer_;
		Timer* update_timer_;
		Timer* running_timer_;
		unsigned int tick_count_;
		unsigned int fps_;
		unsigned int milliseconds_last_frame_;
};


#endif // GAME_BASE_HPP
