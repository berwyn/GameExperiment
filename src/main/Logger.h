#pragma once

#include <string>
#include <memory>

class Logger
{

public:
    inline static Logger* GetInstance() { return instance.get(); }
    void Log(std::string*);
    void Debug(std::string*);
    void Warn(std::string*);
    void Error(std::string*);
    void Fatal(std::string*);

private:
    static std::unique_ptr<Logger> instance;

};