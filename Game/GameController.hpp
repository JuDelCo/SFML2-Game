#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP


#include "../Engine/Includes.hpp"
#include "Includes.hpp"


class GameController : public GameBase
{
	public:
		EventManager1<void, int> event_handler_;
		GameController() {}
		~GameController() {}

	private:
		void Init();
		void OnTick();
		void OnRender();
		void OnEvent(const int event_type, const int param_1, const int param_2);
		void Reset();
		void End();
};


#endif // GAME_CONTROLLER_HPP
