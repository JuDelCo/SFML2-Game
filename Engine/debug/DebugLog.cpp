// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "DebugLog.hpp"
#include "../Defines.hpp"
#include <iostream>
#include <stdarg.h>

Debug::Debug()
{
	m_logStrings.clear();
}

Debug::~Debug()
{
	closeFile();
}

bool Debug::openFile(std::string fileName)
{
	closeFile();

	try
	{
		m_logger.open(fileName, std::ios_base::trunc);
	}
	catch (std::ifstream::failure e)
	{
		return false;
	}

	if(m_logger.is_open())
	{
		return true;
	}

	return false;
}

void Debug::closeFile()
{
	if(m_logger.is_open())
	{
		m_logger.close();
	}
}

bool Debug::loadStrings(std::string fileName)
{
	std::ifstream fileInput(fileName);

	if (!fileInput.is_open())
	{
		return false;
	}

	std::string stringLine;

	while(getline(fileInput, stringLine))
	{
		m_logStrings.push_back(std::string(stringLine));
	}

	return true;
}

void Debug::write(int target, std::string message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message.c_str(), args);

	if (target == LOG_FILE || target == LOG_ALL)
	{
		if(m_logger.is_open())
		{
			m_logger << buffer << "\n";
			m_logger.flush();
		}
	}

	if (target == LOG_CONSOLE || target == LOG_ALL)
	{
		std::cout << buffer << std::endl;
	}

	va_end(args);
}

bool Debug::write(int target, unsigned long messageId, ...)
{
	if(m_logStrings.empty() || m_logStrings.size() <= messageId)
	{
		return false;
	}

	va_list args;
	va_start(args, messageId);
	char buffer[1024];
	vsprintf(buffer, m_logStrings[messageId].c_str(), args);

	write(target, buffer);

	va_end(args);

	return true;
}
