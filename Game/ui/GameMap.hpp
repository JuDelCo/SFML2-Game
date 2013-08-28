#pragma once
#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP


#include "ElementInterface.hpp"


class GameMap : public IElement
{
	public:
		GameMap(sf::IntRect rect, GameData* gameData);
		~GameMap();
		void onTick();
		void onRender();
		void onEvent(int eventType, int param1, int param2);
};


#endif // GAME_MAP_HPP
