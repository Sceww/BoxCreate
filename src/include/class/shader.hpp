#pragma once
#include <string>
// class to help automatically load vert / frag shaders.

class shader {
private:
    std::string sourceCode;
    std::string sourcePath;
    
public:
    shader(std::string filePath);
    ~shader();

    const char* getSource();
    void updateSource();
};