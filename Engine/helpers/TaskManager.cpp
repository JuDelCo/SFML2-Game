// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "TaskManager.hpp"
#include <algorithm>
#include <cassert>

bool ITaskManager::addTask(ITask::Ptr& task)
{
	if (!task->start())
	{
		return false;
	}

	auto it = m_taskList.begin();

	for (; it != m_taskList.end(); ++it)
	{
		ITask::Ptr& comp = (*it);

		if (comp->m_priority > task->m_priority)
		{
			break;
		}
	}

	m_taskList.insert(it, task);

	return true;
}

void ITaskManager::updateTaskList()
{
	while (!m_taskList.empty())
	{
		for (auto task : m_taskList)
		{
			if(!task->m_isFinished)
			{
				task->update();
			}
		}

		for (auto it = m_taskList.begin(); it != m_taskList.end(); ++it)
		{
			if ((*it)->m_isFinished)
			{
				(*it)->stop();
				m_taskList.erase(it);
				(*it) = 0;
			}
		}
	}
}

void ITaskManager::suspendTask(ITask::Ptr& task)
{
	if (std::find(m_taskList.begin(), m_taskList.end(), task) != m_taskList.end())
	{
		task->onSuspend();
		m_taskList.remove(task);
		m_pausedTaskList.emplace_back(task);
	}
}

void ITaskManager::resumeTask(ITask::Ptr& task)
{
	if (std::find(m_pausedTaskList.begin(), m_pausedTaskList.end(), task) != m_pausedTaskList.end())
	{
		task->onResume();
		m_pausedTaskList.remove(task);

		auto it = m_taskList.begin();

		for (; it != m_taskList.end(); ++it)
		{
			ITask::Ptr& comp = (*it);

			if (comp->m_priority > task->m_priority)
			{
				break;
			}
		}

		m_taskList.insert(it, task);
	}
}

void ITaskManager::removeTask(ITask::Ptr& task)
{
	assert(task && "Tried to remove a null task.");

	if (std::find(m_taskList.begin(), m_taskList.end(), task) != m_taskList.end())
	{
		task->m_isFinished = true;

		return;
	}

	auto it = std::find(m_pausedTaskList.begin(), m_pausedTaskList.end(), task);

	if (it != m_taskList.end())
	{
		task->stop();
		m_pausedTaskList.erase(it);

		return;
	}
}

void ITaskManager::killAllTasks()
{
	for (auto it : m_taskList)
	{
		it->m_isFinished = true;
	}

	for (auto it : m_pausedTaskList)
	{
		it->stop();
	}

	m_pausedTaskList.clear();
}
