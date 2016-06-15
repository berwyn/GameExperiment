#include "ShaderLoader.h"
#include "Platform.h"
#include "../main/UTFHelpers.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>

#ifndef WINDOWS

#include <libgen.h>
#include <sys/mman.h>

#endif

#ifdef __APPLE__

#include <mach-o/dyld.h>

#endif

#include "../main/Logger.h"

uint32_t ShaderLoader::LoadShaderFromSource(uint32_t type, std::string* name)
{
    uint32_t shader = glCreateShader(type);
    auto src = loadSource(name).c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    
    int32_t status;
    int32_t infoLogStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogStatus);
    
    if(status == GL_TRUE)
    {
        return shader;
    }
    else
    {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        auto str = std::string(buffer);
        Logger::GetInstance()->Fatal(&str);
        return -1; // Won't actually hit, because fatal
    }
}

std::string ShaderLoader::loadSource(std::string* name)
{
    std::string basePath;
    
#if defined(APPLE)
    
    char nsBasePath[PATH_MAX];
    uint32_t size = sizeof(nsBasePath);
    if(_NSGetExecutablePath(nsBasePath, &size) != 0)
    {
        std::cerr << "Couldn't get base path for " << name << std::endl;
        std::cerr << std::endl << std::endl << nsBasePath << std::endl << std::endl;
        return "";
    }
    basePath = dirname(nsBasePath);

#elif defined(WINDOWS)

    HMODULE module = GetModuleHandle(NULL);
    WCHAR path[MAX_PATH];
    GetModuleFileName(module, path, MAX_PATH);
    basePath = narrow(path);

#else
    // TODO: Implement Linux version :(
#endif
    
    std::string content;
    std::fstream fileStream(basePath + "/assets/shaders/" + name->c_str());
    
    if(!fileStream.is_open())
    {
        std::ostringstream out;
        out << "File "
            << basePath
            << "/assets/shaders/"
            << name
            << " couldn't be opened";
        auto str = out.str();
        Logger::GetInstance()->Fatal(&str);
    }
    
    std::string line;
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    
    fileStream.close();
    return content;
}