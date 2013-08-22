#ifndef MOTION_HPP
#define MOTION_HPP


class Motion
{
	public:
		Motion(const float initial_value, const float max_velocity, const float acceleration);
		~Motion();
		void NewValue(const float new_value, const float time_start);
		void OnTick(const float time_milliseconds);
		void Reset();
		void set_initial_value(const float initial_value);
		float get_initial_value();
		float get_max_velocity();
		float get_acceleration();
		float get_value();
		float get_desired_value();
		float get_speed();
		int get_phase();
		bool is_in_progress();
		bool is_in_ajust();

	private:
		float initial_value_;
		float max_velocity_;
		float acceleration_;
		float value_;
		float desired_value_;
		float speed_;
		int phase_;
		bool in_progress_;
		bool in_ajust_;
		float time_started_;
		float previous_motion_;
		float total_time_;
		float tau_;
		signed int signo_;
		float previous_value_;
		float previous_time_;
};


#endif // MOTION_HPP
