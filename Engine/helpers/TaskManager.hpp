#pragma once
#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP


#include <memory>
#include <list>
#include "TaskInterface.hpp"

#define taskPtr std::shared_ptr<ITask>


class ITaskManager : public ITask
{
	public:
		ITaskManager(unsigned int priority = 10000) : ITask(priority) {}
		~ITaskManager() {}

		bool addTask(taskPtr& task);
		void updateTaskList();
		void suspendTask(taskPtr& task);
		void resumeTask(taskPtr& task);
		void removeTask(taskPtr& task);
		void killAllTasks();

	protected:
		std::list<taskPtr> m_taskList;
		std::list<taskPtr> m_pausedTaskList;
};


#endif // TASK_MANAGER_HPP
