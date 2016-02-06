#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>

#include "Logger.h"

std::unique_ptr<Logger> Logger::instance = std::make_unique<Logger>();

void Logger::Log(std::string* msg)
{
	std::ostringstream buf;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	buf << "[LOG][";
	buf << std::put_time(std::localtime(&now_c), "%F %T");
	buf << "] ";
	buf << *msg;

	std::cout << buf.str() << std::endl;
}

void Logger::Debug(std::string* msg)
{
	std::ostringstream buf;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	buf << "[DBG][";
	buf << std::put_time(std::localtime(&now_c), "%F %T");
	buf << "] ";
	buf << *msg;

	std::cout << buf.str() << std::endl;
}

void Logger::Warn(std::string* msg)
{
	std::ostringstream buf;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	buf << "[WRN][";
	buf << std::put_time(std::localtime(&now_c), "%F %T");
	buf << "] ";
	buf << *msg;

	std::cout << buf.str() << std::endl;
}

void Logger::Error(std::string* msg)
{
	std::ostringstream buf;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	buf << "[ERR][";
	buf << std::put_time(std::localtime(&now_c), "%F %T");
	buf << "] ";
	buf << *msg;

	std::cerr << buf.str() << std::endl;
}

void Logger::Fatal(std::string* msg)
{
	std::ostringstream buf;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	buf << "[FTL][";
	buf << std::put_time(std::localtime(&now_c), "%F %T");
	buf << "] ";
	buf << *msg;

	std::cerr << buf.str() << std::endl;
}