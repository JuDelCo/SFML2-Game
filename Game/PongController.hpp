#ifndef PONG_CONTROLLER_HPP
#define PONG_CONTROLLER_HPP


#include "../Engine/Includes.hpp"


class Pong : public GameBase
{
	public:
		EventManager1<void, int> event_handler_;
		Pong();
		~Pong();

	private:
		void Init();
		void OnTick();
		void OnRender();
		void OnEvent(const int event_type, const int param_1, const int param_2);
		void Reset();
		void End();

		Vector2f ball_pos_;
		Vector2u ball_mov_;
		Vector2f player_pos_;
		Vector2f cpu_pos_;
		unsigned int player_score_;
		unsigned int cpu_score_;
		sf::Font fuente_ = sf::Font();
		sf::Text marcador_;
};


#endif // PONG_CONTROLLER_HPP
