#ifndef DEBUG_LOG_INTERFACE_HPP
#define DEBUG_LOG_INTERFACE_HPP


#include <string>

const int LOG_FILE = 1;
const int LOG_CONSOLE = 2;


class IDebug
{
	public:
		virtual ~IDebug() {};

		virtual bool LoadStrings() = 0;
		virtual void Write(int target, const char* message, ...) = 0;
		virtual void Write(int target, unsigned long message_id, ...) = 0;
};


#endif // DEBUG_LOG_INTERFACE_HPP
