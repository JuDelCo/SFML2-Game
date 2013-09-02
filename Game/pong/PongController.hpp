#pragma once
#ifndef PONG_CONTROLLER_HPP
#define PONG_CONTROLLER_HPP


#include "../../Engine/Includes.hpp"


class Pong : public GameBase
{
	public:
		EventManager1<void, int> m_eventHandler;
		Pong();
		~Pong();

	private:
		void init();
		void onTick();
		void onRender();
		void onEvent(const int eventType, const int param1, const int param2);
		void reset();
		void end();
};


#endif // PONG_CONTROLLER_HPP
