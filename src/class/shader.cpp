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
    shaderHandle = glCreateShader(shaderType);
    updateSource();
}

// destructor for our shader class
shader::~shader() {
    /* ??? */
}

// updates sourceCode
const void shader::updateSource() { // since this method modifies member variables, it should NOT be const...?
    std::ifstream fileSource(sourcePath);
    std::stringstream fileStream;
    
    fileStream << fileSource.rdbuf();
    fileSource.close();

    std::string sourceCode = fileStream.str();
    const char* source = sourceCode.c_str();

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

    // std::cout << "final contents of sourceCode:\n   " << sourceCode << std::endl;
}

const uint32_t shader::getShaderHandle() {
    return shaderHandle;
}

// const char* shader::getSource() {
//     return sourceCode.c_str();
// }

