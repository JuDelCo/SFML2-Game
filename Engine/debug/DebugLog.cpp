#include "DebugLog.hpp"
#include <iostream>
#include <fstream>
#include <stdarg.h>


Debug::Debug()
{
	m_logger.open("log.txt", std::ios_base::trunc);
}


Debug::~Debug()
{
	m_logger.close();
}


void Debug::write(int target, const char* message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);

	if (target & LOG_FILE)
	{
		m_logger << buffer << "\n";
		m_logger.flush();
	}

	if (target & LOG_CONSOLE)
	{
		std::cout << message << std::endl;
	}

	va_end(args);
}


void Debug::write(int target, unsigned long messageId, ...)
{
	va_list args;
	va_start(args, messageId);
	char buffer[1024];
	vsprintf(buffer, m_logStrings[messageId].c_str(), args);

	write(target, buffer);

	va_end(args);
}


bool Debug::loadStrings()
{
	std::ifstream in("strings.txt");

	if (!in.is_open())
	{
		return false;
	}

	unsigned long index = 0;

	while (!in.eof())
	{
		char buffer[1024];
		in.getline(buffer, 1024);
		m_logStrings[index++] = buffer;
	}

	return true;
}
