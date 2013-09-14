#pragma once
#ifndef TECH_DEMO_CONTROLLER_HPP
#define TECH_DEMO_CONTROLLER_HPP


#include "../../Engine/Includes.hpp"


class TechDemo : public GameBase
{
	public:
		EventManager1<void, int> m_eventHandler;
		TechDemo();
		~TechDemo();

	private:
		void onTick();
		void onRender();
		void onEvent(const int eventType, const int param1, const int param2);

		TileMap* m_tileMap;
};


typedef std::shared_ptr<TechDemo> TechDemoPtr;


#endif // TECH_DEMO_CONTROLLER_HPP
