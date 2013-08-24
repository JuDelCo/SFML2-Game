#ifndef DEBUG_LOG_INTERFACE_HPP
#define DEBUG_LOG_INTERFACE_HPP


#include <string>

const int LOG_FILE = 1;
const int LOG_CONSOLE = 2;


class IDebug
{
	public:
		virtual ~IDebug() {};

		virtual bool loadStrings() = 0;
		virtual void write(int target, const char* message, ...) = 0;
		virtual void write(int target, unsigned long messageId, ...) = 0;
};


#endif // DEBUG_LOG_INTERFACE_HPP
