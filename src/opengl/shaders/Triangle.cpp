#ifndef APPLE
#include <gl/glew.h>
#endif

#include "Platform.h"
#include "Triangle.h"
#include "../ShaderLoader.h"

TriangleShader::~TriangleShader(){}

void TriangleShader::Init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    float_t vertexData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    
    auto loader = ShaderLoader::GetInstance();
    
    std::string fragmentName = std::string("Triangle.fs.glsl");
    vertex = loader.LoadShaderFromSource(GL_FRAGMENT_SHADER, &fragmentName);
    std::string vertexName = std::string("Triangle.vs.glsl");
    fragment = loader.LoadShaderFromSource(GL_VERTEX_SHADER, &vertexName);
    
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glBindFragDataLocation(program, 0, "outColor");
    glLinkProgram(program);
    glUseProgram(program);
    
    uint32_t posAttrib = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void TriangleShader::Draw()
{
    glUseProgram(program);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}