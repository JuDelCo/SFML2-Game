#pragma once
#ifndef REGION_INTERFACE_HPP
#define REGION_INTERFACE_HPP


#include "ElementInterface.hpp"


class IRegion : public IElement
{
	public:
		IRegion(sf::IntRect rect, GameData* gameData);
		~IRegion();
		void onTick();
		void onRender();
		void onEvent(int eventType, int param1, int param2);
};


#endif // REGION_INTERFACE_HPP
