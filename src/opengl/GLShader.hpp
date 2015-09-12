#ifndef GLSHADER_H
#define GLSHADER_H

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

GLuint LoadShader(const char* vertex_path, GLenum shader_type);

#endif