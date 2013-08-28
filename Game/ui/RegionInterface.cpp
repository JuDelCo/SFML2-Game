#include "RegionInterface.hpp"


IRegion::IRegion(sf::IntRect rect, GameData* gameData) : IElement(rect, gameData)
{
}

IRegion::~IRegion()
{
}

void IRegion::onTick()
{
	m_gameData->testFunction();
}

void IRegion::onRender()
{
}

void IRegion::onEvent(int eventType, int param1, int param2)
{
}
