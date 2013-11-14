// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef DEBUG_LOG_HPP
#define DEBUG_LOG_HPP

#include <fstream>
#include <vector>
#include <string>
#include <memory>

class Debug
{
	public:
		typedef std::shared_ptr<Debug> Ptr;

		Debug();
		~Debug();

		bool openFile(std::string fileName);
		void closeFile();
		bool loadStrings(std::string fileName);
		void write(int target, std::string message, ...);
		bool write(int target, unsigned long messageId, ...);

	private:
		std::vector<std::string> m_logStrings;
		std::ofstream m_logger;
};

#endif // DEBUG_LOG_HPP
