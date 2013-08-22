#ifndef ELEMENT_INTERFACE_HPP
#define ELEMENT_INTERFACE_HPP


#include <SFML/Graphics.hpp>
#include "../GameData.hpp"


class IElement
{
	public:
		IElement(IntRect rect, GameData* game_data);
		virtual ~IElement() {};
		bool is_enabled();
		void Enable();
		void Disable();
		virtual void OnTick() = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(int eventType, int param1, int param2) = 0;

	protected:
		GameData* game_data;
		IntRect rect;
		bool enabled;
};


#endif // ELEMENT_INTERFACE_HPP
