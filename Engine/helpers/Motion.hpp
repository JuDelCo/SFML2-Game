// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef MOTION_HPP
#define MOTION_HPP

class Motion
{
	public:
		Motion(const float initialValue, const float maxVelocity, const float acceleration);
		~Motion() {}

		void newValue(const float newValue, const float timeStart);
		void onTick(const float timeMs);
		void reset();
		void setInitialValue(const float initialValue);
		float getInitialValue();
		float getMaxVelocity();
		float getAcceleration();
		float getValue();
		float getDesiredValue();
		float getSpeed();
		int getPhase();
		bool isInProgress();
		bool isInAjust();

	private:
		float m_initialValue;
		float m_maxVelocity;
		float m_acceleration;
		float m_value;
		float m_desiredValue;
		float m_speed;
		int m_phase;
		bool m_inProgress;
		bool m_inAjust;
		float m_timeStarted;
		float m_previousMotion;
		float m_totalTime;
		float m_tau;
		signed int m_signo;
		float m_previousValue;
		float m_previousTime;
};

#endif // MOTION_HPP
