#include "DebugLog.hpp"
#include <iostream>
#include <fstream>
#include <stdarg.h>


Debug::Debug()
{
	this->logger_.open("log.txt", std::ios_base::trunc);
}


Debug::~Debug()
{
	this->logger_.close();
}


void Debug::Write(int target, const char* message, ...)
{
	va_list args;
	va_start(args, message);
	char buffer[1024];
	vsprintf(buffer, message, args);

	if(target & LOG_FILE)
	{
		this->logger_ << buffer << "\n";
		this->logger_.flush();
	}

	if(target & LOG_CONSOLE)
	{
		std::cout << message << std::endl;
	}

	va_end(args);
}


void Debug::Write(int target, unsigned long message_id, ...)
{
	va_list args;
	va_start(args, message_id);
	char buffer[1024];
	vsprintf(buffer, this->logStrings_[message_id].c_str(), args);

	this->Write(target, buffer);

	va_end(args);
}


bool Debug::LoadStrings()
{
	std::ifstream in("strings.txt");

	if(!in.is_open())
	{
		return false;
	}

	unsigned long index = 0;

	while(!in.eof())
	{
		char szBuf[1024];
		in.getline(szBuf, 1024);
		this->logStrings_[index++] = szBuf;
	}

	return true;
}
