#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP


#include <memory>
#include <list>
#include "TaskInterface.hpp"

#define task_ptr std::shared_ptr<ITask>


class ITaskManager : public ITask
{
	public:
		ITaskManager(unsigned int priority = 10000) : ITask(priority) {}
		~ITaskManager() {}

		bool AddTask(task_ptr& task);
		void UpdateTaskList();
		void SuspendTask(task_ptr& task);
		void ResumeTask(task_ptr& task);
		void RemoveTask(task_ptr& task);
		void KillAllTasks();

	protected:
		std::list<task_ptr> task_list_;
		std::list<task_ptr> paused_task_list_;
};


#endif // TASK_MANAGER_HPP
