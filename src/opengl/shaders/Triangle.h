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
    void Draw(int32_t renderWidth, int32_t renderHeight);
    
private:
    
    uint32_t vao;
    uint32_t vbo;
    uint32_t cbo;
    uint32_t matrix;
    
};