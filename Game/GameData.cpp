#include "GameData.hpp"


GameData::GameData()
{
}

void GameData::TestFunction()
{
	DEBUG->Write(LOG_FILE, "Line: %u - GameData | TestFunction Called!", __LINE__);
}
