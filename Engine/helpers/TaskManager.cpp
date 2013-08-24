#include "TaskManager.hpp"
#include <algorithm>
#include <cassert>


bool ITaskManager::addTask(taskPtr& task)
{
	if (!task->start())
	{
		return false;
	}

	std::list<taskPtr>::iterator it;

	for (it = m_taskList.begin(); it != m_taskList.end(); it++)
	{
		taskPtr& comp = (*it);

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
		std::list<taskPtr>::iterator it, thisIt;

		for (it = m_taskList.begin(); it != m_taskList.end();)
		{
			taskPtr task = (*it);
			++it;

			if (!task->m_isFinished)
			{
				task->update();
			}
		}

		for (it = m_taskList.begin(); it != m_taskList.end();)
		{
			taskPtr task = (*it);
			thisIt = it;
			++it;

			if (task->m_isFinished)
			{
				task->stop();
				m_taskList.erase(thisIt);
				task = 0;
			}
		}
	}
}


void ITaskManager::suspendTask(taskPtr& task)
{
	if (std::find(m_taskList.begin(), m_taskList.end(), task) != m_taskList.end())
	{
		task->onSuspend();
		m_taskList.remove(task);
		m_pausedTaskList.push_back(task);
	}
}


void ITaskManager::resumeTask(taskPtr& task)
{
	if (std::find(m_pausedTaskList.begin(), m_pausedTaskList.end(), task) != m_pausedTaskList.end())
	{
		task->onResume();
		m_pausedTaskList.remove(task);

		std::list<taskPtr>::iterator it;

		for (it = m_taskList.begin(); it != m_taskList.end(); it++)
		{
			taskPtr& comp = (*it);

			if (comp->m_priority > task->m_priority)
			{
				break;
			}
		}

		m_taskList.insert(it, task);
	}
}


void ITaskManager::removeTask(taskPtr& task)
{
	assert(task && "Tried to remove a null task.");

	if (std::find(m_taskList.begin(), m_taskList.end(), task) != m_taskList.end())
	{
		task->m_isFinished = true;

		return;
	}

	std::list<taskPtr>::iterator it;

	if ((it = std::find(m_pausedTaskList.begin(), m_pausedTaskList.end(), task)) != m_taskList.end())
	{
		task->stop();
		m_pausedTaskList.erase(it);

		return;
	}
}


void ITaskManager::killAllTasks()
{
	for (std::list<taskPtr>::iterator it = m_taskList.begin(); it != m_taskList.end(); it++)
	{
		(*it)->m_isFinished = true;
	}

	std::list<taskPtr>::iterator it;

	for (it = m_pausedTaskList.begin(); it != m_pausedTaskList.end(); it++)
	{
		(*it)->stop();
	}

	m_pausedTaskList.clear();
}
