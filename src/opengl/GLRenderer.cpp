#ifndef APPLE

#include <gl/glew.h>

#endif

#include <chrono>
#include <thread>
#include <time.h>
#include <stdbool.h>

#include "../main/engine/Engine.h"
#include "GLRenderer.h"

bool GLRenderer::Init(uint32_t width, uint32_t height)
{
    
    this->width = width;
    this->height = height;
    
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
    glfwSwapInterval(1);
 
    window = glfwCreateWindow(this->width, this->height, "GameExperiment", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    std::vector<float> vertices = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };
    
    shader = TriangleShader(&vertices);
    
    return true;
}

void GLRenderer::Draw()
{
    static time_t last = time(NULL);
    if(glfwWindowShouldClose(window))
    {
        engine->ShouldHalt = true;
        return;
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shader.program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
    time_t now = time(NULL);
    auto delta = now - last;
    last = now;
    if(delta < 16)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16 - delta));
    }
}
