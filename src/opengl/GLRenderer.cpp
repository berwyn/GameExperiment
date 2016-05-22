#ifndef APPLE
#include <gl/glew.h>
#endif

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

    shader.Init();
    
    return true;
}

void GLRenderer::Draw()
{
    if(glfwWindowShouldClose(window))
    {
        engine->ShouldHalt = true;
        return;
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.Draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}
