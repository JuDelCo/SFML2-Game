// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef INTERPOLATOR_HPP
#define INTERPOLATOR_HPP

class IInterpolator
{
	public:
		IInterpolator();

		virtual ~IInterpolator() {}
		virtual float update(float value) = 0;
		float getValue();
		bool isFinished();

	protected:
		float m_value;
		bool m_finished;
};

class ITimeBasedInterpolator : public IInterpolator
{
	public:
		ITimeBasedInterpolator(float totalTimeMs);

		float update(float elapsedTimeMs);
		void reset();

	protected:
		virtual void calculate() = 0;

		float m_elapsedTime;
		float m_totalTime;
};

class LinearInterpolator : public ITimeBasedInterpolator
{
	public:
		LinearInterpolator(float totalTimeMs, float startValue, float endValue);

	protected:
		void calculate();

		float m_startValue;
		float m_endValue;
};

class QuadraticInterpolator : public ITimeBasedInterpolator
{
	public:
		QuadraticInterpolator(float totalTimeMs, float startValue, float midValue, float endValue);

	protected:
		void calculate();

		float m_startValue;
		float m_midValue;
		float m_endValue;
};

class CubicInterpolator : public ITimeBasedInterpolator
{
	public:
		CubicInterpolator(float totalTimeMs, float startValue, float midValue1, float midValue2, float endValue);

	protected:
		void calculate();

		float m_startValue;
		float m_midValue1;
		float m_midValue2;
		float m_endValue;
};

#endif // INTERPOLATOR_HPP
