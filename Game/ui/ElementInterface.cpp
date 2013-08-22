#include "ElementInterface.hpp"


IElement::IElement(IntRect rect, GameData* game_data)
{
	this->enabled = true;
	this->rect = rect;
	this->game_data = game_data;
}

bool IElement::is_enabled()
{
	return this->enabled;
}

void IElement::Enable()
{
	this->enabled = true;
}

void IElement::Disable()
{
	this->enabled = false;
}
