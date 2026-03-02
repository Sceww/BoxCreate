#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
// class to help automatically load vert / frag shaders.

class shader {
private:
    // std::string sourceCode;
    std::string sourcePath;
    uint32_t shaderHandle;
    int shaderType;
    
public:
    shader(std::string filePath, int SHADER_TYPE);
    ~shader();

    const uint32_t getShaderHandle();
    void updateSource();
};