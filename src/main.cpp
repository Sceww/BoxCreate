#include <iostream>
#include <fstream>

#include <globals.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <class/image.hpp>
#include <class/shader.hpp>
#include <class/shaderProgram.hpp>

void clipSpace_to_screenCoords(double* x, double* y, double width, double height);
void screenCoords_to_clipSpace(double* x, double* y, double width, double height);

const float bounds[VERTEX_ATTRIBUTE_COUNT * 4] = {
    // XYZ                UV
    -0.05,  0.05,  0.0,   0.0, 1.0, // top left
     0.05,  0.05,  0.0,   1.0, 1.0, // top right
    -0.05, -0.05,  0.0,   0.0, 0.0, // bottom left
     0.05, -0.05,  0.0,   1.0, 0.0, // bottom right
};

void createBox(box box[], uint32_t* numBox, uint32_t indices[], uint32_t* numIndices, double x, double y) {
    if (*numBox+1 >= MAX_NUMBER_OF_BOXES) {
        printf("CANNOT CREATE MORE BOXES!\n");
        return;
    }
    for (int i = 0; i < (VERTEX_ATTRIBUTE_COUNT * 4); i += VERTEX_ATTRIBUTE_COUNT) {
        box[*numBox].vertices[i]   = bounds[i]   + (float)x; // 0  x
        box[*numBox].vertices[i+1] = bounds[i+1] + (float)y; // 1  y 
        box[*numBox].vertices[i+2] = bounds[i+2];            // 2  z
        box[*numBox].vertices[i+3] = bounds[i+3];            // 3   u
        box[*numBox].vertices[i+4] = bounds[i+4];            // 4   v
    }
    indices[*numIndices  ] = 0 + 4 * (*numBox);
    indices[*numIndices+1] = 1 + 4 * (*numBox);
    indices[*numIndices+2] = 2 + 4 * (*numBox);
    indices[*numIndices+3] = 1 + 4 * (*numBox);
    indices[*numIndices+4] = 2 + 4 * (*numBox);
    indices[*numIndices+5] = 3 + 4 * (*numBox);

    *numIndices += 6;

    (*numBox)++;
    
    printf("Created box #%d!\n", *numBox);
}

void boxData(box box[], uint32_t numBox, uint32_t indices[], uint32_t numIndices, int vertexArray, int vertexBuffer, int elementBuffer) {
    glBindVertexArray(vertexArray);
}

void click_callback(GLFWwindow* window, int button, int action, int mods) { 
    state_struct* gs = &g_state;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double x,y;
        glfwGetCursorPos(window, &x, &y);
        screenCoords_to_clipSpace(&x, &y, gs->width, gs->height);
        createBox(gs->boxes, &gs->numBoxes, gs->indices, &gs->indicesCount, x, y);
    }
}

void clipSpace_to_screenCoords(double* x, double* y, double width, double height) {
    *x = ((*x * width) + width) / 2.0;
    *y = ((*y * -height) + height) / 2.0;
}

void screenCoords_to_clipSpace(double* x, double* y, double width, double height) {
    *x = ((*x * 2) / width) - 1;
    *y = ((*y * -2) / height) + 1;
}


int main() {
    state_struct* gs = &g_state;

    if (!glfwInit()) { 
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(gs->width, gs->height, "TEST APP", NULL, NULL);

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
    glGenVertexArrays(1, &gs->VAO);
    glGenBuffers(1, &gs->VBO);
    glGenBuffers(1, &gs->EBO);


    // box vertex attributes
    glBindVertexArray(gs->VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ATTRIBUTE_COUNT, (void*)0); // position attrib
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_ATTRIBUTE_COUNT, (void*)(sizeof(float)*3)); // uv attrib
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(NULL);
    
    glfwSetMouseButtonCallback(window, click_callback);

    // PICTURE
    flip_images_on_load(true);

    image dog("../../img/dog.jpg");
    
    program.useProgram();

    program.setInt("texture1", dog.getActiveTextureID());

    glBindVertexArray(NULL); // We NEED to do this to ensure that future unrelated VAO calls don't modify previous attributes!
    // LOOP!
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // width; height;
        glfwGetFramebufferSize(window, &gs->width, &gs->height);
        glViewport(0, 0, gs->width, gs->height);

        float timeVal = glfwGetTime();
        
        glClearColor((sin(timeVal)+1)/2, (sin(timeVal+1)+1)/2, (sin(timeVal+2)+1)/2, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //  /*BOX*/
        program.useProgram(); // activate program...

        program.setFloat("time", timeVal);
        
        // glDrawElements(GL_TRIANGLES, ???, GL_UNSIGNED_INT, ???);
        glBindVertexArray(NULL);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
} // int main()

// }
