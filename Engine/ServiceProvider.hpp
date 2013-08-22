#ifndef SERVICE_PROVIDER_HPP
#define SERVICE_PROVIDER_HPP


class IInput;
class IVideo;
class IDebug;

#define INPUT ServiceProvider::get_input()
#define VIDEO ServiceProvider::get_video()
#define DEBUG ServiceProvider::get_debug()


class ServiceProvider
{
	public:
		static void Provide(IInput* input_service);
		static void Provide(IVideo* video_service);
		static void Provide(IDebug* debug_service);
		static IInput* get_input();
		static IVideo* get_video();
		static IDebug* get_debug();

	private:
		static IInput* input_service_;
		static IVideo* video_service_;
		static IDebug* debug_service_;
};


#endif // SERVICE_PROVIDER_HPP
