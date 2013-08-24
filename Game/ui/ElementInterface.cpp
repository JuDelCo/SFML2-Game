#include "ElementInterface.hpp"


IElement::IElement(IntRect rect, GameData* gameData)
{
	m_enabled = true;
	m_rect = rect;
	m_gameData = gameData;
}

bool IElement::isEnabled()
{
	return m_enabled;
}

void IElement::enable()
{
	m_enabled = true;
}

void IElement::disable()
{
	m_enabled = false;
}
