#include "Timer.hpp"
#include <SFML/system.hpp>


#define getElapsedTimeMs() getElapsedTime().asMilliseconds()


Timer::Timer()
{
	this->clock_ = new sf::Clock();

	this->start_ticks_ = 0;
	this->paused_ticks_ = 0;
	this->paused_ = false;
	this->started_ = false;
}


Timer::~Timer()
{
	delete this->clock_;
}


void Timer::Start()
{
	this->started_ = true;
	this->paused_ = false;
	this->start_ticks_ = this->clock_->getElapsedTimeMs();
}


void Timer::Pause()
{
	if((this->started_ == true) && (this->paused_ == false))
	{
		this->paused_ = true;
		this->paused_ticks_ = this->clock_->getElapsedTimeMs() - this->start_ticks_;
	}
}


void Timer::Continue()
{
	if(this->paused_ == true)
	{
		this->paused_ = false;
		this->start_ticks_ = this->clock_->getElapsedTimeMs() - this->paused_ticks_;
		this->paused_ticks_ = 0;
	}
}


void Timer::Stop()
{
	this->started_ = false;
	this->paused_ = false;
}


unsigned int Timer::get_ticks()
{
	if(this->started_ == true)
	{
		if(this->paused_ == true)
		{
			return this->paused_ticks_;
		}
		else
		{
			return this->clock_->getElapsedTimeMs() - this->start_ticks_;
		}
	}

	return 0;
}


bool Timer::is_started()
{
	return this->started_;
}


bool Timer::is_paused()
{
	return this->paused_;
}
