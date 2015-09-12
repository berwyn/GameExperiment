#include "GLShader.hpp"

#include <stdio.h>
#include <sys/mman.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <libgen.h>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

std::string readFile(const char* filePath)
{
	std::string basePath;

	#ifdef __APPLE__

	char nsBasePath[PATH_MAX];
	uint32_t size = sizeof(nsBasePath);
	if(_NSGetExecutablePath(nsBasePath, &size) != 0)
	{
		std::cerr << "Couldn't get base path for " << filePath << std::endl;
		std::cerr << std::endl << std::endl << nsBasePath << std::endl << std::endl;
		return "";
	}
	basePath = dirname(nsBasePath);

	#endif

	std::string content;
	std::fstream fileStream(basePath + '/' + filePath);

	if(!fileStream.is_open())
	{
		std::cerr << "File " << filePath << " could not be opened" << std::endl;
		return "";
	}

	std::string line = "";
	while(!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line);
		content.append("\n");
	}

	fileStream.close();
	return content;
}

GLuint LoadShader(const char* vertex_path, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);
	std::string shaderStr = readFile(vertex_path);
	const char* shaderSrc = shaderStr.c_str();

	GLint result = GL_FALSE;
	int logLength;

	std::cout << "Compiling shader " << vertex_path << "\n" << shaderSrc << std::endl;
	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

	if(result != GL_TRUE)
	{
		std::cout << vertex_path << " failed to compile\n" << std::endl;
	}

	char* buffer;
	glGetShaderInfoLog(shader, logLength, nullptr, buffer);
	std::cout << std::string(buffer) << "\n" << std::endl;

	return shader;
}
