#ifndef APPLE
#include <GL/glew.h>
#endif

#include "GLVertexBuffer.h"

namespace Game::OpenGL
{
    GLVertexBuffer::GLVertexBuffer() : IVertexBuffer()
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &cbo);
    };

    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &cbo);
        glDeleteVertexArrays(1, &vao);
    }

    bool GLVertexBuffer::LoadStaticMesh(std::vector<float_t> vertices)
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

        return true;
    }

    bool GLVertexBuffer::LoadStaticColors(std::vector<float_t> colors)
    {
        glBindBuffer(GL_ARRAY_BUFFER, cbo);
        glBufferData(GL_ARRAY_BUFFER, colors.size(), colors.data(), GL_STATIC_DRAW);

        return true;
    }
}
