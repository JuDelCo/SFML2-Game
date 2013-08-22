#include "TaskManager.hpp"
#include <algorithm>
#include <cassert>


bool ITaskManager::AddTask(task_ptr& task)
{
	if(!task->Start())
	{
		return false;
	}

	std::list<task_ptr>::iterator it;

	for(it = task_list_.begin(); it != task_list_.end(); it++)
	{
		task_ptr& comp = (*it);

		if(comp->priority_ > task->priority_)
		{
			break;
		}
	}

	task_list_.insert(it, task);

	return true;
}


void ITaskManager::UpdateTaskList()
{
	while(!task_list_.empty())
	{
		std::list<task_ptr>::iterator it, thisIt;

		for(it = task_list_.begin(); it != task_list_.end();)
		{
			task_ptr task = (*it);
			++it;

			if(!task->is_finished_)
			{
				task->Update();
			}
		}

		for(it = task_list_.begin(); it != task_list_.end();)
		{
			task_ptr task = (*it);
			thisIt = it;
			++it;

			if(task->is_finished_)
			{
				task->Stop();
				task_list_.erase(thisIt);
				task = 0;
			}
		}
	}
}


void ITaskManager::SuspendTask(task_ptr& task)
{
	if(std::find(task_list_.begin(), task_list_.end(), task) != task_list_.end())
	{
		task->OnSuspend();
		task_list_.remove(task);
		paused_task_list_.push_back(task);
	}
}


void ITaskManager::ResumeTask(task_ptr& task)
{
	if(std::find(paused_task_list_.begin(), paused_task_list_.end(), task) != paused_task_list_.end())
	{
		task->OnResume();
		paused_task_list_.remove(task);

		std::list<task_ptr>::iterator it;

		for(it = task_list_.begin(); it != task_list_.end(); it++)
		{
			task_ptr& comp = (*it);

			if(comp->priority_ > task->priority_)
			{
				break;
			}
		}

		task_list_.insert(it, task);
	}
}


void ITaskManager::RemoveTask(task_ptr& task)
{
	assert(task && "Tried to remove a null task.");

	if(std::find(task_list_.begin(), task_list_.end(), task) != task_list_.end())
	{
		task->is_finished_ = true;

		return;
	}

	std::list<task_ptr>::iterator it;

	if((it = std::find(paused_task_list_.begin(), paused_task_list_.end(), task)) != task_list_.end())
	{
		task->Stop();
		paused_task_list_.erase(it);

		return;
	}
}


void ITaskManager::KillAllTasks()
{
	for(std::list<task_ptr>::iterator it = task_list_.begin(); it != task_list_.end(); it++)
	{
		(*it)->is_finished_ = true;
	}

	std::list<task_ptr>::iterator it;

	for(it = paused_task_list_.begin(); it != paused_task_list_.end(); it++)
	{
		(*it)->Stop();
	}

	paused_task_list_.clear();
}
