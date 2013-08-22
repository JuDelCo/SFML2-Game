#include "RegionInterface.hpp"


IRegion::IRegion(IntRect rect, GameData* game_data) : IElement(rect, game_data)
{
}

IRegion::~IRegion()
{
}

void IRegion::OnTick()
{
	this->game_data->TestFunction();
}

void IRegion::OnRender()
{
}

void IRegion::OnEvent(int eventType, int param1, int param2)
{
}
