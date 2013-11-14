// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include <memory>
#include <list>
#include "TaskInterface.hpp"

class ITaskManager : public ITask
{
	public:
		ITaskManager(unsigned int priority = 10000) : ITask(priority) {};
		~ITaskManager() {}

		bool addTask(ITask::Ptr& task);
		void updateTaskList();
		void suspendTask(ITask::Ptr& task);
		void resumeTask(ITask::Ptr& task);
		void removeTask(ITask::Ptr& task);
		void killAllTasks();

	protected:
		std::list<ITask::Ptr> m_taskList;
		std::list<ITask::Ptr> m_pausedTaskList;
};

#endif // TASK_MANAGER_HPP
