#pragma once

#include <stdint.h>
#include <vector>

class TriangleShader
{
public:
    
    uint32_t vertex;
    uint32_t fragment;
    uint32_t program;
    
    TriangleShader(std::vector<float>* vertices);
    ~TriangleShader();
    
private:
    
    uint32_t vao;
    uint32_t vbo;
    
};