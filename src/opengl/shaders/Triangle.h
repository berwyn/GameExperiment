#pragma once


#include <math.h>
#include <stdint.h>
#include <vector>

class TriangleShader
{
public:
    
    uint32_t vertex;
    uint32_t fragment;
    uint32_t program;
    
    inline TriangleShader(){};
    ~TriangleShader();
    
    void Init();
    void Draw();
    
private:
    
    uint32_t vao;
    uint32_t vbo;
    
};