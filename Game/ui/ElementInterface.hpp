#pragma once
#ifndef ELEMENT_INTERFACE_HPP
#define ELEMENT_INTERFACE_HPP


#include <SFML/Graphics.hpp>
#include "../GameData.hpp"


class IElement
{
	public:
		IElement(sf::IntRect rect, GameData* gameData);
		virtual ~IElement() {};
		bool isEnabled();
		void enable();
		void disable();
		virtual void onTick() = 0;
		virtual void onRender() = 0;
		virtual void onEvent(int eventType, int param1, int param2) = 0;

	protected:
		GameData* m_gameData;
		sf::IntRect m_rect;
		bool m_enabled;
};


#endif // ELEMENT_INTERFACE_HPP
