#pragma once
#include <class/shader.hpp>

class shaderProgram
{
private:
    shader* vert;
    shader* frag;

    uint32_t program;
public:
    shaderProgram(shader* VERTEX_SHADER, shader* FRAGMENT_SHADER);
    ~shaderProgram();

    void relinkProgram();
    const int getProgramHandle();
    const void useProgram();
};


