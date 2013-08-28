#pragma once
#ifndef SERVICE_PROVIDER_HPP
#define SERVICE_PROVIDER_HPP


class IInput;
class IVideo;
class IDebug;

#define INPUT ServiceProvider::getInput()
#define VIDEO ServiceProvider::getVideo()
#define DEBUG ServiceProvider::getDebug()


class ServiceProvider
{
	public:
		static void provide(IInput* inputService);
		static void provide(IVideo* videoService);
		static void provide(IDebug* debugService);
		static IInput* getInput();
		static IVideo* getVideo();
		static IDebug* getDebug();

	private:
		static IInput* m_inputService;
		static IVideo* m_videoService;
		static IDebug* m_debugService;
};


#endif // SERVICE_PROVIDER_HPP
