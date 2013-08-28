#pragma once
#ifndef TASK_INTERFACE_HPP
#define TASK_INTERFACE_HPP


class ITask
{
	public:
		ITask(unsigned int priority = 10000) : m_isFinished(false), m_priority(priority) {}
		~ITask() {}

		virtual bool start() = 0;
		virtual void update() = 0;
		virtual void stop() = 0;
		virtual void onSuspend() {};
		virtual void onResume() {};

		bool m_isFinished;
		unsigned int m_priority;
};


#endif // TASK_INTERFACE_HPP
