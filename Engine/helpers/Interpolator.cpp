// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "Interpolator.hpp"
#include "Util.hpp"

IInterpolator::IInterpolator()
{
	m_value = 0;
	m_finished = false;
}

float IInterpolator::getValue()
{
	return m_value;
}

bool IInterpolator::isFinished()
{
	return m_finished;
}

ITimeBasedInterpolator::ITimeBasedInterpolator(float totalTimeMs)
{
	m_totalTime = totalTimeMs;
	m_elapsedTime = 0;
}

float ITimeBasedInterpolator::update(float elapsedTimeMs)
{
	if(!m_finished)
	{
		m_elapsedTime += elapsedTimeMs;

		calculate();

		if (m_elapsedTime >= m_totalTime)
		{
			m_finished = true;
		}
	}

	return m_value;
}

void ITimeBasedInterpolator::reset()
{
	m_elapsedTime = 0;
	m_finished = false;
}

LinearInterpolator::LinearInterpolator(float totalTimeMs, float startValue, float endValue) : ITimeBasedInterpolator(totalTimeMs)
{
	m_startValue = startValue;
	m_endValue = endValue;

	calculate();
}

void LinearInterpolator::calculate()
{
	float b = clamp(m_elapsedTime / m_totalTime, 0, 1);
	float a = (1 - b);

	m_value = (m_startValue * a) + (m_endValue * b);
}

QuadraticInterpolator::QuadraticInterpolator(float totalTimeMs, float startValue, float midValue, float endValue) : ITimeBasedInterpolator(totalTimeMs)
{
	m_startValue = startValue;
	m_midValue = midValue;
	m_endValue = endValue;

	calculate();
}

void QuadraticInterpolator::calculate()
{
	float b = clamp(m_elapsedTime / m_totalTime, 0, 1);
	float a = (1 - b);

	m_value = (m_startValue * a * a) + (m_midValue * 2 * a * b) + (m_endValue * b * b);
}

CubicInterpolator::CubicInterpolator(float totalTimeMs, float startValue, float midValue1, float midValue2, float endValue) : ITimeBasedInterpolator(totalTimeMs)
{
	m_startValue = startValue;
	m_midValue1 = midValue1;
	m_midValue2 = midValue2;
	m_endValue = endValue;

	calculate();
}

void CubicInterpolator::calculate()
{
	float b = clamp(m_elapsedTime / m_totalTime, 0, 1);
	float a = (1 - b);

	m_value = (m_startValue * a * a * a) + (m_midValue1 * 3 * a * a * b) + (m_midValue2 * 3 * a * b * b) + (m_endValue * b * b * b);
}
