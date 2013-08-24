#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP


#include "../Engine/Includes.hpp"
#include "Includes.hpp"


class GameController : public GameBase
{
	public:
		EventManager1<void, int> m_eventHandler;
		GameController() {}
		~GameController() {}

	private:
		void init();
		void onTick();
		void onRender();
		void onEvent(const int eventType, const int param1, const int param2);
		void reset();
		void end();
};


#endif // GAME_CONTROLLER_HPP
