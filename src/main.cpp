#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <class/shader.hpp>

void printInfo(double time, int frames);

int main() {
    if (!glfwInit()) { 
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 640, "TEST APP", NULL, NULL);

    if (!window) {
        glfwTerminate(); 
        return -1; 
    }
    glfwMakeContextCurrent(window);

    /* GLAD init */
    uint32_t version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to init OpenGL context!\n");
        return -1;
    }
    printf("Successfully loaded OpenGL! %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    };
    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // attempt to load a shader from file...
    // TODO: error handling!
    shader frag("../../src/gl/frag/shader.frag", GL_FRAGMENT_SHADER);
    shader vert("../../src/gl/vert/shader.vert", GL_VERTEX_SHADER);

    // COMPILING SHADERS AND STUFF...
    
        /*SHADERS*/
    uint32_t fragShader = frag.getShaderHandle();
    uint32_t vertShader = vert.getShaderHandle();
    
        /*VAO*/
    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
        /*EBO*/
    uint32_t EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        /*VBO*/
    uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*VertexAttribs*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // in attribute 0, we have 3 values for a combined size of 4*3 bytes, with no offset position
    glEnableVertexAttribArray(0);

        /*PROGRAM*/
    uint32_t shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    
    // LOOP!
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}