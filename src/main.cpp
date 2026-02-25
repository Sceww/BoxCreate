#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <class/shader.hpp>
#include <class/shaderProgram.hpp>

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
    
    float box[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
    };
    float triangle[] {
        -1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    uint32_t boxIndices[] = {
        0, 1, 3,
        1, 2, 3
    };
    uint32_t triIndices[] = {
        0, 1, 2
    };

    // attempt to load a shader from file...
    // TODO: error handling!
    shader frag("../../src/gl/frag/shader.frag", GL_FRAGMENT_SHADER);
    shader frag2("../../src/gl/frag/shader2.frag", GL_FRAGMENT_SHADER);
    shader vert("../../src/gl/vert/shader.vert", GL_VERTEX_SHADER);

    // COMPILING SHADERS AND STUFF...
    
    /* OBJECTS */
        /*VBO, VAO*/
    uint32_t VAO[2], VBO[2], EBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    //Object 1 (Box)
    glBindVertexArray(VAO[0]);
        /*VBO*/
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);    
    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);
        /*EBO*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);
        /*Wrap up*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0 ); // each 'object' with a VertexArrayObject needs to define its own Attribute Pointers (?)
    glEnableVertexAttribArray(0);

    glBindVertexArray(NULL); // Doesn't need to be here currently, but is good practice...

    //Object 2 (Triangle)
    glBindVertexArray(VAO[1]); // What exactly do VAOs store????

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triIndices), triIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0 ); // define vertex attribute of object 2...
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(NULL); // We NEED to do this to ensure that future unrelated VAO calls don't modify previous attributes!

    /*PROGRAM*/
    shaderProgram program(&frag, &vert);
    shaderProgram program2(&frag2, &vert);

    glBindVertexArray(0);
    // LOOP!
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw objects here!
            /*TRIANGLE*/
        program2.useProgram();
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
            /*BOX*/
        program.useProgram();
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}