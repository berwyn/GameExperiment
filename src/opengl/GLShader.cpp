#include "GLShader.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::string readFile(const char* filePath)
{
	std::string content;
	std::fstream fileStream(filePath, std::ios::in);
	
	if(!fileStream.is_open())
	{
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}
	
	std::string line = "";
	while(!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
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
	
	std::cout << "Compiling shader " << vertex_path << " " << std::endl;
	glShaderSource(shader, 1, &shaderSrc, nullptr);
	glCompileShader(shader);
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> shaderErr((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, nullptr, &shaderErr[0]);
	std::cout << &shaderErr[0] << std::endl;
	
	return shader;
}