#include "GameBase.hpp"
#include "Defines.hpp"
#include "ServiceProvider.hpp"
#include "debug/DebugLog.hpp"
#include "input/Input.hpp"
#include "video/Video.hpp"
#include "helpers/Timer.hpp"


GameBase::GameBase(unsigned int size_x, unsigned int size_y) : event_listener_(this, &GameBase::OnEvent)
{
	IDebug* debug_service = new Debug();
	ServiceProvider::Provide(debug_service);

	IVideo* video_service = new Video(size_x, size_y);
	ServiceProvider::Provide(video_service);

	IInput* input_service = new Input();
	input_service->event_handler_.Add(&this->event_listener_);

	//input_service->event_handler_.Add(EventListenerBase3<ReturnT, ParamT1, ParamT2, ParamT3> *slot)
	//input_service->event_handler_.Attach(ListenerT *object, ReturnT (ListenerT::*member)(ParamT1, ParamT2, ParamT3));
	//input_service->event_handler_.Detach(int id);

	//event_listener_.Add(Event3<void, int, int, int> *cpp_event);
	//event_listener_.Remove();

	ServiceProvider::Provide(input_service);

	this->running_timer_ = new Timer();
	this->fps_timer_ = new Timer();
	this->update_timer_ = new Timer();
}


GameBase::~GameBase()
{
	delete this->running_timer_;
	delete this->fps_timer_;
	delete this->update_timer_;
}


void GameBase::Start()
{
	this->run_ = true;

	this->Loop();
}


void GameBase::Stop()
{
	this->run_ = false;
}


unsigned int GameBase::get_time_running()
{
	return this->running_timer_->get_ticks();
}


unsigned int GameBase::get_tick_count()
{
	return this->tick_count_;
}


unsigned int GameBase::get_fps()
{
	return this->fps_;
}


unsigned int GameBase::get_milliseconds_last_frame()
{
	return this->milliseconds_last_frame_;
}


void GameBase::DelayMilliseconds(const unsigned int delay_milliseconds)
{
	sf::sleep(sf::milliseconds(delay_milliseconds));
}


void GameBase::Loop()
{
	this->SystemInit();

	IInput* input = ServiceProvider::get_input();

	while(this->run_)
	{
		this->milliseconds_last_frame_ = this->fps_timer_->get_ticks();

		if(this->milliseconds_last_frame_ > 1000.0f / FPS_LIMIT)
		{
			this->milliseconds_last_frame_ = (int)(1000.0f / FPS_LIMIT);
		}

		this->fps_timer_->Start();

		input->OnTick();
		this->OnTick();
		++this->tick_count_;

		this->OnRender();

		if(this->update_timer_->get_ticks() >= 1000)
		{
			this->fps_ = this->fps_counter_;
			this->fps_counter_ = 0;
			this->update_timer_->Start();
		}

		++this->fps_counter_;

		if(this->fps_timer_->get_ticks() < 17)  //59fps
		{
			this->DelayMilliseconds(17 - this->fps_timer_->get_ticks());
		}
	}

	this->SystemEnd();
}


void GameBase::SystemInit()
{
	this->fps_counter_ = 0;
	this->fps_ = FPS_LIMIT;
	this->milliseconds_last_frame_ = 0;

	this->Init();

	this->running_timer_->Start();
	this->update_timer_->Start();
}


void GameBase::SystemEnd()
{
	this->End();

	this->update_timer_->Stop();
	this->fps_timer_->Stop();
	this->running_timer_->Stop();
}
