#pragma once

#include <string>

class Logger
{

public:
	inline static Logger* GetInstance() { return instance; }
	void Log(std::string*);
	void Debug(std::string*);
	void Warn(std::string*);
	void Error(std::string*);
	void Fatal(std::string*);

private:
	static Logger* instance;

};