#ifndef DEBUG_LOG_HPP
#define DEBUG_LOG_HPP


#include <fstream>
#include "DebugLogInterface.hpp"
#define MAX_LOG_STRINGS 256


class Debug : public IDebug
{
	public:
		Debug();
		~Debug();

		bool loadStrings();
		void write(int target, const char* message, ...);
		void write(int target, unsigned long messageId, ...);

	private:
		std::string m_logStrings[MAX_LOG_STRINGS];
		std::ofstream m_logger;
};


#endif // DEBUG_LOG_HPP
