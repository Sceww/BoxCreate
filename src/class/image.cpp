#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <class/image.hpp>

void flip_images_on_load(int boolean) {
    stbi_set_flip_vertically_on_load(boolean);
}

static int number_of_textures = 0;

image::image(const char* filePath) {
    int width, height, nrChannels;
    unsigned char* imageData = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (imageData) {
        activeTextureID = number_of_textures++;
        printf("Successfully loaded image[%d]!\n", activeTextureID);
        glGenTextures(1, &textureHandle);
        glActiveTexture(GL_TEXTURE0 + activeTextureID);
        glBindTexture(GL_TEXTURE_2D, textureHandle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("ERROR LOADING IMAGE! : %s\n", filePath);
    }

    stbi_image_free(imageData);
}

image::~image() {
    // ????
}

const uint32_t image::getTextureHandle() {
    return textureHandle;
}

const uint32_t image::getActiveTextureID() {
    return activeTextureID;
}