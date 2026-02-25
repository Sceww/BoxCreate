#include <class/shaderProgram.hpp>

// takes a vertex and a fragment shader and compiles a shader program
shaderProgram::shaderProgram(shader* VERTEX_SHADER, shader* FRAGMENT_SHADER) {
    vert = VERTEX_SHADER;
    frag = FRAGMENT_SHADER;
    program = NULL;

    relinkProgram();
}

shaderProgram::~shaderProgram(){
    // ???
}

void shaderProgram::relinkProgram(){
    // checks if program currently exists
    if (glIsProgram(program)) {
        // Delete program and create a new one
        printf("Reloading shaders...\n");
        glDeleteProgram(program);
        vert->updateSource();
        frag->updateSource();
    };
    program = glCreateProgram();
    glAttachShader(program, vert->getShaderHandle());
    glAttachShader(program, frag->getShaderHandle());
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::LINKING SHADER PROGRAM! : %s", infoLog);
    }
}

const void shaderProgram::useProgram(){
    glUseProgram(program);
}

const int shaderProgram::getProgramHandle() {
    return program;
}