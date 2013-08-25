#include "ServiceProvider.hpp"
#include "input/InputInterface.hpp"
#include "video/VideoInterface.hpp"
#include "debug/DebugLogInterface.hpp"


IInput* ServiceProvider::m_inputService = nullptr;
IVideo* ServiceProvider::m_videoService = nullptr;
IDebug* ServiceProvider::m_debugService = nullptr;


void ServiceProvider::provide(IInput* inputService)
{
	ServiceProvider::m_inputService = inputService;
}


void ServiceProvider::provide(IVideo* videoService)
{
	ServiceProvider::m_videoService = videoService;
}


void ServiceProvider::provide(IDebug* debugService)
{
	ServiceProvider::m_debugService = debugService;
}


IInput* ServiceProvider::getInput()
{
	return ServiceProvider::m_inputService;
}


IVideo* ServiceProvider::getVideo()
{
	return ServiceProvider::m_videoService;
}


IDebug* ServiceProvider::getDebug()
{
	return ServiceProvider::m_debugService;
}
