#include "GameData.hpp"


GameData::GameData()
{
}

void GameData::testFunction()
{
	DEBUG->write(LOG_FILE, "Line: %u - GameData | TestFunction Called!", __LINE__);
}
