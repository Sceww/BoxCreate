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

void printInfo(double time, int frames);
// static void cursorPositionCallback(GLFWwindow* window, double x, double y);


int main() {
    if (!glfwInit()) { 
        return -1;
    }
    int width = 800, height = 640;
    GLFWwindow* window = glfwCreateWindow(width, height, "TEST APP", NULL, NULL);
    // glfwSetCursorPosCallback(window, cursorPositionCallback);

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
        // POSITIONAL DATA   // COLOR DATA    // UV
        0.5f,  0.5f, 0.0f,   1.0, 0.0, 0.0,   1.0, 1.0,  // top right
        0.5f, -0.5f, 0.0f,   0.0, 1.0, 0.0,   1.0, 0.0,  // bottom right
       -0.5f, -0.5f, 0.0f,   0.0, 0.0, 1.0,   0.0, 0.0,  // bottom left
       -0.5f,  0.5f, 0.0f,   1.0, 1.0, 1,0,   1.0, 0.0   // top left
    };
    uint32_t boxIndices[] = {
        0, 1, 3, // tri 1
        1, 2, 3  // tri 2
    };

    // attempt to load a shader from file...
    // TODO: error handling!
    shader frag("../../src/gl/frag/shader.frag", GL_FRAGMENT_SHADER);
    // shader frag2("../../src/gl/frag/shader2.frag", GL_FRAGMENT_SHADER);
    shader vert("../../src/gl/vert/shader.vert", GL_VERTEX_SHADER);

    // COMPILING SHADERS AND STUFF...
    
        /*PROGRAM*/
    shaderProgram program(&frag, &vert);
    // shaderProgram program2(&frag2, &vert);

    /* OBJECTS */
        /*VBO, VAO*/
    const int numArray = 1;
    uint32_t VAO[numArray], VBO[numArray], EBO[numArray];
    glGenVertexArrays(numArray, VAO);
    glGenBuffers(numArray, VBO);
    glGenBuffers(numArray, EBO);

    //Object 1 (Box)
    glBindVertexArray(VAO[0]);
        /*VBO*/
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);      /* If we want to update our vertices later, we'd have to call glBindBuffer() with 
                                                    A.) The correct VertexArrayObject binded
                                                    B.) glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW)*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW); // static draw places these vertices in a slower read cache.
        /*EBO*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boxIndices), boxIndices, GL_STATIC_DRAW);
        /*Wrap up*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0 ); // each 'object' with a VertexArrayObject needs to define its own Attribute Pointers (?)
    glEnableVertexAttribArray(0); // vertex pos
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1); // vertex color
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2); // uv
    // PICTURE
    flip_images_on_load(true);

    image dog("../../img/dog.jpg");
    image rabbit("../../img/meatball.jpg");
    
    program.useProgram();

    program.setInt("texture1", dog.getActiveTextureID());
    program.setInt("texture2", rabbit.getActiveTextureID());

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
        
        // convert to NDC...
        xPos = ((xPos*2) / width)-1;
        yPos = ((yPos*-2) / height)+1;

        // world origin
        glm::mat4 worldOrig(1.0);
        // camera transform
        glm::mat4 camera(1.0);
        camera = glm::translate(camera, glm::vec3(0.0, 0.0, ((sin(timeVal)*3 - 5))));
        camera = glm::rotate(camera, glm::radians(timeVal*20), glm::vec3(0.0, 1.0, 0.0));
        // projection transform
        glm::mat4 perspective(1.0);
        perspective = glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 100.0f);

        glm::mat4 modelTrans(1.0);
        modelTrans = glm::translate(modelTrans, glm::vec3(xPos, yPos, 0.0));
        modelTrans = glm::rotate(modelTrans, glm::radians(timeVal*100), glm::vec3(1.0, 0.0, 0.0));
        modelTrans = glm::rotate(modelTrans, glm::radians((float)xPos * 100.0f), glm::vec3(0.0, 1.0, 0.0));
        modelTrans = glm::rotate(modelTrans, glm::radians((float)yPos * 100.0f), glm::vec3(0.0, 0.0, 1.0));

        
        program.setFloat("time", timeVal);
        
        glUniformMatrix4fv(transformHandle, 1, GL_FALSE, glm::value_ptr(modelTrans)); //
        glUniformMatrix4fv(camHandle, 1, GL_FALSE, glm::value_ptr(camera));
        glUniformMatrix4fv(projHandle, 1, GL_FALSE, glm::value_ptr(perspective));

        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
} // int main()

// static void cursorPositionCallback(GLFWwindow* window, double x, double y) {

// }
