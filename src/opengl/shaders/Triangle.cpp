#include "Platform.h"
#include "Triangle.h"
#include "../ShaderLoader.h"

TriangleShader::TriangleShader(std::vector<float>* vertices)
{
    if(vertices == nullptr) return;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    auto data = vertices->data();
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    
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
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

TriangleShader::~TriangleShader()
{
    
}