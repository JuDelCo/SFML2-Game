#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP


#include "ElementInterface.hpp"


class GameMap : public IElement
{
	public:
		GameMap(IntRect rect, GameData* game_data);
		~GameMap();
		void OnTick();
		void OnRender();
		void OnEvent(int eventType, int param1, int param2);
};


#endif // GAME_MAP_HPP
