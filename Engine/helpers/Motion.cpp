#include "Motion.hpp"
#include <math.h>


Motion::Motion(const float initial_value, const float max_velocity, const float acceleration)
{
	this->initial_value_ = initial_value;
	this->max_velocity_ = max_velocity;
	this->acceleration_ = acceleration;

	this->Reset();
}


Motion::~Motion()
{
}


void Motion::NewValue(const float new_value, const float time_start)
{
	if(this->value_ != new_value)
	{
		if(this->speed_ == 0.0)
		{
			this->in_ajust_ = false;

			this->desired_value_ = new_value;
			this->previous_motion_ = this->value_;
			this->previous_value_ = this->value_;
			this->previous_time_ = (float)(time_start / 1000);

			if(this->desired_value_ >= this->previous_value_)
			{
				this->signo_ = 1;
			}
			else
			{
				this->signo_ = -1;
			}

			this->time_started_ = (float)(time_start / 1000);
			this->tau_ = this->max_velocity_ / this->acceleration_;
			this->total_time_ = this->signo_ * ((this->desired_value_ - this->previous_value_) / this->max_velocity_) + this->tau_;

			if((this->acceleration_ * this->tau_ * this->tau_) / 2 > this->signo_ * (this->desired_value_ - this->previous_value_) / 2)
			{
				this->total_time_ = sqrt((2 * (this->signo_ * (this->desired_value_ - this->previous_value_)) / 2) / this->acceleration_) * 2;
				this->tau_ = this->total_time_ / 2;
			}

			this->in_progress_ = true;
		}
		else if(new_value != this->desired_value_)
		{
			float e = this->value_ + this->signo_ * ((this->speed_ * this->speed_) / this->acceleration_) / 2;

			if((this->value_ > e && new_value < e) || (this->value_ < e && new_value > e))
			{
				this->in_ajust_ = false;

				this->desired_value_ = new_value;

				this->time_started_ = (float)(time_start / 1000) - (this->speed_ / this->acceleration_);
				this->previous_motion_ = this->value_ - this->signo_ * ((this->speed_ * this->speed_) / this->acceleration_) / 2;

				this->tau_ = this->max_velocity_ / this->acceleration_;
				this->total_time_ = this->signo_ * ((this->desired_value_ - this->previous_motion_) / this->max_velocity_) + this->tau_;

				if((this->acceleration_ * this->tau_ * this->tau_) / 2 > this->signo_ * (this->desired_value_ - this->previous_motion_) / 2)
				{
					this->total_time_ = sqrt((2 * (this->signo_ * (this->desired_value_ - this->previous_motion_)) / 2) / this->acceleration_) * 2;
					this->tau_ = this->total_time_ / 2;
				}

				this->previous_value_ = this->value_;
				this->previous_time_ = this->time_started_;

				this->in_progress_ = true;
			}
			else
			{
				this->in_progress_ = false;
				this->phase_ = 0;

				this->time_started_ = (float)(time_start / 1000);
				this->total_time_ = this->speed_ / this->acceleration_;
				this->desired_value_ = new_value;
				this->previous_motion_ = this->value_;
				this->previous_value_ = this->value_;
				this->previous_time_ = this->time_started_;

				if((this->previous_value_ + this->signo_ * (this->acceleration_ * this->total_time_ * this->total_time_) / 2) >= this->previous_value_)
				{
					this->signo_ = 1;
				}
				else
				{
					this->signo_ = -1;
				}

				this->in_ajust_ = true;
			}
		}
	}
}


void Motion::OnTick(const float time_milliseconds)
{
	if(this->in_progress_)
	{
		float time = (float)(time_milliseconds / 1000);
		time -= this->time_started_;

		if(time >= this->total_time_)
		{
			this->phase_ = 0;
			this->value_ = this->desired_value_;
			this->previous_value_ = this->value_;
			this->in_progress_ = false;
		}
		else if((this->total_time_ - this->tau_) < time)
		{
			this->phase_ = 3;
			this->value_ =
				this->desired_value_ +
				this->signo_ *
				(
					-((this->acceleration_ * this->total_time_ * this->total_time_) / 2) +
					(this->acceleration_ * this->total_time_ * time) - ((this->acceleration_ / 2) * time * time)
				);
		}
		else if(this->tau_ < time && time <= (this->total_time_ - this->tau_))
		{
			this->phase_ = 2;
			this->value_ =
				this->previous_motion_ -
				(this->signo_ * ((this->max_velocity_ * this->max_velocity_) / (2 * this->acceleration_))) +
				(this->signo_ * this->max_velocity_ * time);
		}
		else
		{
			this->phase_ = 1;
			this->value_ = this->previous_motion_ + (this->signo_ * (this->acceleration_ / 2) * time * time);
		}

		this->speed_ = -(this->signo_) * (this->previous_value_ - this->value_) / (time - this->previous_time_);
		this->previous_value_ = this->value_;
		this->previous_time_ = time;
	}
	else if(this->in_ajust_)
	{
		float time = (float)(time_milliseconds / 1000);
		time -= this->time_started_;

		if(time >= this->total_time_)
		{
			this->speed_ = 0.0;
			this->in_ajust_ = false;

			this->NewValue(this->desired_value_, time_milliseconds);
		}
		else
		{
			this->value_ =
				(this->previous_motion_ + this->signo_ * (this->acceleration_ * this->total_time_ * this->total_time_) / 2) +
				this->signo_ *
				(
					-((this->acceleration_ * this->total_time_ * this->total_time_) / 2) +
					(this->acceleration_ * this->total_time_ * time) - ((this->acceleration_ / 2) * time * time)
				);

			this->speed_ = -(this->signo_) * (this->previous_value_ - this->value_) / (time - this->previous_time_);
			this->previous_value_ = this->value_;
			this->previous_time_ = time;
		}
	}
}


void Motion::Reset()
{
	this->value_ = this->initial_value_;
	this->desired_value_ = this->initial_value_;
	this->speed_ = 0.0;

	this->phase_ = 0;
	this->in_progress_ = false;
	this->in_ajust_ = false;
	this->time_started_ = 0.0;
	this->previous_motion_ = 0.0;
	this->total_time_ = 0.0;
	this->tau_ = 0.0;
	this->signo_ = 1;
	this->previous_value_ = 0.0;
	this->previous_time_ = 0.0;
}


void Motion::set_initial_value(const float initial_value)
{
	this->initial_value_ = initial_value;
}


float Motion::get_initial_value()
{
	return this->initial_value_;
}


float Motion::get_max_velocity()
{
	return this->max_velocity_;
}


float Motion::get_acceleration()
{
	return this->acceleration_;
}


float Motion::get_value()
{
	return this->value_;
}


float Motion::get_desired_value()
{
	return this->desired_value_;
}


float Motion::get_speed()
{
	return this->speed_;
}


int Motion::get_phase()
{
	return this->phase_;
}


bool Motion::is_in_progress()
{
	return this->in_progress_;
}


bool Motion::is_in_ajust()
{
	return this->in_ajust_;
}
