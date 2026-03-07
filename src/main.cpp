#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <class/image.hpp>
#include <class/shader.hpp>
#include <class/shaderProgram.hpp>

void clipSpace_to_screenCoords(double* x, double* y, double width, double height) {
    *x = ((*x * width) + width) / 2.0;
    *y = ((*y * -height) + height) / 2.0;
}

void screenCoords_to_clipSpace(double* x, double* y, double width, double height) {
    *x = ((*x * 2) / width) - 1;
    *y = ((*y * 2) / height) + 1;
}

int main() {
    if (!glfwInit()) { 
        return -1;
    }
    int width = 800, height = 640;
    GLFWwindow* window = glfwCreateWindow(width, height, "TEST APP", NULL, NULL);

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

    // attempt to load a shader from file...
    // TODO: error handling!
    shader frag("../../src/gl/frag/shader.frag", GL_FRAGMENT_SHADER);
    shader vert("../../src/gl/vert/shader.vert", GL_VERTEX_SHADER);

    // COMPILING SHADERS AND STUFF...
    
        /*PROGRAM*/
    shaderProgram program(&frag, &vert);

    /* OBJECTS */
        /*VBO, VAO*/
    const int numArray = 1;
    uint32_t VAO[numArray], VBO[numArray], EBO[numArray];
    glGenVertexArrays(numArray, VAO);
    glGenBuffers(numArray, VBO);
    glGenBuffers(numArray, EBO);

    // PICTURE
    flip_images_on_load(true);

    image dog("../../img/dog.jpg");
    
    program.useProgram();

    program.setInt("texture1", dog.getActiveTextureID());

    int transformHandle = program.getUniformHandle("modelTrans");
    int camHandle = program.getUniformHandle("view");
    int projHandle = program.getUniformHandle("projection");

    glBindVertexArray(NULL); // We NEED to do this to ensure that future unrelated VAO calls don't modify previous attributes!
    
    glBindVertexArray(0);
    // LOOP!
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // width; height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        float timeVal = glfwGetTime();
        
        glClearColor((sin(timeVal)+1)/2, (sin(timeVal+1)+1)/2, (sin(timeVal+2)+1)/2, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //  /*BOX*/
        program.useProgram(); // activate program...
        
        // grab mouse pos...
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        
        screenCoords_to_clipSpace(&xPos, &yPos, width, height);
        
        program.setFloat("time", timeVal);

        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
} // int main()

// }
