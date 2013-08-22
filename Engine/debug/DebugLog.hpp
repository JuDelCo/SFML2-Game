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

		bool LoadStrings();
		void Write(int target, const char* message, ...);
		void Write(int target, unsigned long message_id, ...);

	private:
		std::string logStrings_[MAX_LOG_STRINGS];
		std::ofstream logger_;
};


#endif // DEBUG_LOG_HPP
