// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Motion.hpp"
#include <math.h>

Motion::Motion(const float initialValue, const float maxVelocity, const float acceleration)
{
	m_initialValue = initialValue;
	m_maxVelocity = maxVelocity;
	m_acceleration = acceleration;

	reset();
}

void Motion::newValue(const float newValue, const float timeStart)
{
	if (m_value != newValue)
	{
		if (m_speed == 0.0)
		{
			m_inAjust = false;

			m_desiredValue = newValue;
			m_previousMotion = m_value;
			m_previousValue = m_value;
			m_previousTime = (float)(timeStart / 1000);

			if (m_desiredValue >= m_previousValue)
			{
				m_signo = 1;
			}
			else
			{
				m_signo = -1;
			}

			m_timeStarted = (float)(timeStart / 1000);
			m_tau = m_maxVelocity / m_acceleration;
			m_totalTime = m_signo * ((m_desiredValue - m_previousValue) / m_maxVelocity) + m_tau;

			if ((m_acceleration * m_tau * m_tau) / 2 > m_signo * (m_desiredValue - m_previousValue) / 2)
			{
				m_totalTime = sqrt((2 * (m_signo * (m_desiredValue - m_previousValue)) / 2) / m_acceleration) * 2;
				m_tau = m_totalTime / 2;
			}

			m_inProgress = true;
		}
		else if (newValue != m_desiredValue)
		{
			float e = m_value + m_signo * ((m_speed * m_speed) / m_acceleration) / 2;

			if ((m_value > e && newValue < e) || (m_value < e && newValue > e))
			{
				m_inAjust = false;

				m_desiredValue = newValue;

				m_timeStarted = (float)(timeStart / 1000) - (m_speed / m_acceleration);
				m_previousMotion = m_value - m_signo * ((m_speed * m_speed) / m_acceleration) / 2;

				m_tau = m_maxVelocity / m_acceleration;
				m_totalTime = m_signo * ((m_desiredValue - m_previousMotion) / m_maxVelocity) + m_tau;

				if ((m_acceleration * m_tau * m_tau) / 2 > m_signo * (m_desiredValue - m_previousMotion) / 2)
				{
					m_totalTime = sqrt((2 * (m_signo * (m_desiredValue - m_previousMotion)) / 2) / m_acceleration) * 2;
					m_tau = m_totalTime / 2;
				}

				m_previousValue = m_value;
				m_previousTime = m_timeStarted;

				m_inProgress = true;
			}
			else
			{
				m_inProgress = false;
				m_phase = 0;

				m_timeStarted = (float)(timeStart / 1000);
				m_totalTime = m_speed / m_acceleration;
				m_desiredValue = newValue;
				m_previousMotion = m_value;
				m_previousValue = m_value;
				m_previousTime = m_timeStarted;

				if ((m_previousValue + m_signo * (m_acceleration * m_totalTime * m_totalTime) / 2) >= m_previousValue)
				{
					m_signo = 1;
				}
				else
				{
					m_signo = -1;
				}

				m_inAjust = true;
			}
		}
	}
}

void Motion::onTick(const float timeMs)
{
	if (m_inProgress)
	{
		float time = (float)(timeMs / 1000);
		time -= m_timeStarted;

		if (time >= m_totalTime)
		{
			m_phase = 0;
			m_value = m_desiredValue;
			m_previousValue = m_value;
			m_inProgress = false;
		}
		else if ((m_totalTime - m_tau) < time)
		{
			m_phase = 3;
			m_value =
				m_desiredValue +
				m_signo *
				(
					-((m_acceleration * m_totalTime * m_totalTime) / 2) +
					(m_acceleration * m_totalTime * time) - ((m_acceleration / 2) * time * time)
				);
		}
		else if (m_tau < time && time <= (m_totalTime - m_tau))
		{
			m_phase = 2;
			m_value =
				m_previousMotion -
				(m_signo * ((m_maxVelocity * m_maxVelocity) / (2 * m_acceleration))) +
				(m_signo * m_maxVelocity * time);
		}
		else
		{
			m_phase = 1;
			m_value = m_previousMotion + (m_signo * (m_acceleration / 2) * time * time);
		}

		m_speed = -(m_signo) * (m_previousValue - m_value) / (time - m_previousTime);
		m_previousValue = m_value;
		m_previousTime = time;
	}
	else if (m_inAjust)
	{
		float time = (float)(timeMs / 1000);
		time -= m_timeStarted;

		if (time >= m_totalTime)
		{
			m_speed = 0.0;
			m_inAjust = false;

			newValue(m_desiredValue, timeMs);
		}
		else
		{
			m_value =
				(m_previousMotion + m_signo * (m_acceleration * m_totalTime * m_totalTime) / 2) +
				m_signo *
				(
					-((m_acceleration * m_totalTime * m_totalTime) / 2) +
					(m_acceleration * m_totalTime * time) - ((m_acceleration / 2) * time * time)
				);

			m_speed = -(m_signo) * (m_previousValue - m_value) / (time - m_previousTime);
			m_previousValue = m_value;
			m_previousTime = time;
		}
	}
}

void Motion::reset()
{
	m_value = m_initialValue;
	m_desiredValue = m_initialValue;
	m_speed = 0.0;

	m_phase = 0;
	m_inProgress = false;
	m_inAjust = false;
	m_timeStarted = 0.0;
	m_previousMotion = 0.0;
	m_totalTime = 0.0;
	m_tau = 0.0;
	m_signo = 1;
	m_previousValue = 0.0;
	m_previousTime = 0.0;
}

void Motion::setInitialValue(const float initialValue)
{
	m_initialValue = initialValue;
}

float Motion::getInitialValue()
{
	return m_initialValue;
}

float Motion::getMaxVelocity()
{
	return m_maxVelocity;
}

float Motion::getAcceleration()
{
	return m_acceleration;
}

float Motion::getValue()
{
	return m_value;
}

float Motion::getDesiredValue()
{
	return m_desiredValue;
}

float Motion::getSpeed()
{
	return m_speed;
}

int Motion::getPhase()
{
	return m_phase;
}

bool Motion::isInProgress()
{
	return m_inProgress;
}

bool Motion::isInAjust()
{
	return m_inAjust;
}
