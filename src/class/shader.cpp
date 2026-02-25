#include <class/shader.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// constructor for our shader class

shader::shader(std::string filePath, int SHADER_TYPE) {
    // reads sourceCode from filePath; initializes sourcePath...
    sourcePath = filePath;
    shaderType = SHADER_TYPE;
    shaderHandle = NULL;
    updateSource();
}

// destructor for our shader class
shader::~shader() {
    /* ??? */
}

// updates sourceCode
void shader::updateSource() {
    std::ifstream fileSource(sourcePath);
    std::stringstream fileStream;
    
    fileStream << fileSource.rdbuf();
    fileSource.close();

    std::string sourceCode = fileStream.str();
    const char* source = sourceCode.c_str();

    if (glIsShader(shaderHandle)) {
        glDeleteShader(shaderHandle);
    }
    
    shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, NULL);
    glCompileShader(shaderHandle);

    // CHECK IF SHADER COMPILED CORRECTLY!!!!!!!!!!!!!!!!
    int success;
    char infoLog[512]; 
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
        printf("ERROR::SHADER FAILED TO COMPILE: %s\n", infoLog);
    } else {
        printf("%d: SHADER SUCCESSFULLY COMPILED!\n", shaderHandle);
    }
}

const uint32_t shader::getShaderHandle() {
    return shaderHandle;
}
