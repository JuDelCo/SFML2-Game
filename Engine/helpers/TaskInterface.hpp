#ifndef TASK_INTERFACE_HPP
#define TASK_INTERFACE_HPP


class ITask
{
	public:
		ITask(unsigned int priority = 10000) : is_finished_(false), priority_(priority) {}
		~ITask() {}

		virtual bool Start() = 0;
		virtual void Update() = 0;
		virtual void Stop() = 0;
		virtual void OnSuspend() {};
		virtual void OnResume() {};

		bool is_finished_;
		unsigned int priority_;
};


#endif // TASK_INTERFACE_HPP
