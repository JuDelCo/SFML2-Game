#include "SpriteAnimated.hpp"
#include "../ServiceProvider.hpp"
#include "../debug/DebugLog.hpp"
#include "../Defines.hpp"


SpriteAnimated::SpriteAnimated()
{
	this->current_frame_ = 0;
	this->num_frames_ = 1;
	this->frame_width_ = 0;
	this->frame_time_ = 0;
	this->time_remain_ = this->frame_time_;
}


SpriteAnimated::SpriteAnimated(const std::string location, const int num_frames, const int delay)
{
	this->LoadTexture(location, num_frames);

	this->current_frame_ = 0;
	this->frame_time_ = delay;
	this->time_remain_ = this->frame_time_;

	this->setTextureRect(sf::IntRect(0, 0, this->frame_width_, this->getTexture()->getSize().y));
}


SpriteAnimated::~SpriteAnimated()
{
}


void SpriteAnimated::LoadTexture(const std::string location, const int num_frames)
{
	if(!this->image_.loadFromFile(location))
	{
		DEBUG->Write(LOG_FILE, "Unable to load sprite from: %s", location.c_str());
		exit(ERROR_SPRITELOAD);
	}

	this->setTexture(this->image_);

	this->num_frames_ = num_frames;
	this->frame_width_ = this->getTexture()->getSize().x / this->num_frames_;

	this->setTextureRect(sf::IntRect(0, 0, this->frame_width_, this->getTexture()->getSize().y));
}


void SpriteAnimated::Update(const int& milliseconds_last_frame)
{
	if(this->frame_time_ > 0)
	{
		this->time_remain_ -= milliseconds_last_frame; // Revisar si hubiera problema al congelar la pantalla (moverla)

		if(this->time_remain_ <= 0)
		{
			if(++this->current_frame_ > (this->num_frames_ - 1))
			{
				this->current_frame_ = 0;
			}

			this->time_remain_ = this->frame_time_;
		}

		this->setTextureRect(sf::IntRect((this->current_frame_ * this->frame_width_), 0, this->frame_width_, this->getTexture()->getSize().y));
	}
}


int SpriteAnimated::get_current_frame()
{
	return this->current_frame_;
}


int SpriteAnimated::get_frame_width()
{
	return this->frame_width_;
}


int SpriteAnimated::get_num_of_frames()
{
	return this->num_frames_;
}


int SpriteAnimated::get_delay()
{
	return this->frame_time_;
}


void SpriteAnimated::set_current_frame(const int current_frame)
{
	this->current_frame_ = current_frame;

	this->setTextureRect(sf::IntRect((this->current_frame_ * this->frame_width_), 0, this->frame_width_, this->getTexture()->getSize().y));
}


void SpriteAnimated::set_frame_width(const int frame_width)
{
	this->frame_width_ = frame_width;
}


void SpriteAnimated::set_num_of_frames(const int num_frames)
{
	this->num_frames_ = num_frames;
}


void SpriteAnimated::set_delay(const int delay)
{
	this->frame_time_ = delay;
}
