#version 330 core

uniform mat4 mvp;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    fragmentColor = vertexColor;
}