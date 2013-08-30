#pragma once
#ifndef DEBUG_LOG_HPP
#define DEBUG_LOG_HPP


#include <fstream>
#include <string>
#define MAX_LOG_STRINGS 256


const int LOG_FILE = 1;
const int LOG_CONSOLE = 2;


class Debug
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
