#include <class/shader.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// constructor for our shader class

shader::shader(std::string filePath) {
    // reads sourceCode from filePath; initializes sourcePath...
    sourcePath = filePath;
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

    sourceCode = fileStream.str();

    // std::cout << "final contents of sourceCode:\n   " << sourceCode << std::endl;
}

const char* shader::getSource() {
    return sourceCode.c_str();
}

