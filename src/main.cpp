#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to init OpenGL context!\n");
        return -1;
    }
    printf("Successfully loaded OpenGL! %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    
    double oldT = 0.0;
    double newT = 0.0; 
    double delta = 0.0;
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        newT = glfwGetTime();
        delta = newT - oldT;
        oldT = newT;
        
        double val = ( sin(newT) + 1 ) / 2;
        
        printf("delta: %f | sin(time): %f\r", delta, val);

    }

    glfwTerminate();
    return 0;
}