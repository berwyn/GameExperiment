#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "GLShader.hpp"

class Game
{
public:
	bool Init()
	{
		if(!glfwInit())
		{
			return false;
		}
		
		#ifndef __APPLE__

		glewExperimental = GL_TRUE;
		glewInit();
		
		#endif
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr);
		
		return true;
	}
	
	void Loop()
	{
		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		
		float vertices[] = {
			0.0f,  0.5f,
			0.5f, -0.5f,
			-0.5f, -0.5f
		};
		
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glfwMakeContextCurrent(window);
		while(!glfwWindowShouldClose(window))
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	
	void Terminate()
	{
		glfwTerminate();
	}
	
private:
	GLFWwindow* window;
}