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
 
    window = glfwCreateWindow(this->width, this->height, "GameExperiment", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    return true;
}

void GLRenderer::Draw()
{
    glfwPollEvents();
    if(glfwWindowShouldClose(window))
    {
        engine->ShouldHalt = true;
    }
    
    float verties[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };
    
    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verties), verties, GL_STATIC_DRAW);
}