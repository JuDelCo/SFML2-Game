#pragma once
#ifndef DEBUG_LOG_HPP
#define DEBUG_LOG_HPP


#include <fstream>
#include <vector>
#include <string>


class Debug
{
	public:
		Debug();
		~Debug();

		bool openFile(std::string fileName);
		void closeFile();
		bool loadStrings(std::string fileName);
		void write(int target, const char* message, ...);
		bool write(int target, unsigned long messageId, ...);

	private:
		std::vector<std::string> m_logStrings;
		std::ofstream m_logger;
};


#endif // DEBUG_LOG_HPP
