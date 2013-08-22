#include "ServiceProvider.hpp"
#include "input/InputInterface.hpp"
#include "video/VideoInterface.hpp"
#include "debug/DebugLogInterface.hpp"


IInput* ServiceProvider::input_service_ = NULL;
IVideo* ServiceProvider::video_service_ = NULL;
IDebug* ServiceProvider::debug_service_ = NULL;


void ServiceProvider::Provide(IInput* input_service)
{
	ServiceProvider::input_service_ = input_service;
}


void ServiceProvider::Provide(IVideo* video_service)
{
	ServiceProvider::video_service_ = video_service;
}


void ServiceProvider::Provide(IDebug* debug_service)
{
	ServiceProvider::debug_service_ = debug_service;
}


IInput* ServiceProvider::get_input()
{
	return ServiceProvider::input_service_;
}


IVideo* ServiceProvider::get_video()
{
	return ServiceProvider::video_service_;
}


IDebug* ServiceProvider::get_debug()
{
	return ServiceProvider::debug_service_;
}
