#ifndef REGION_INTERFACE_HPP
#define REGION_INTERFACE_HPP


#include "ElementInterface.hpp"


class IRegion : public IElement
{
	public:
		IRegion(IntRect rect, GameData* game_data);
		~IRegion();
		void OnTick();
		void OnRender();
		void OnEvent(int eventType, int param1, int param2);
};


#endif // REGION_INTERFACE_HPP
