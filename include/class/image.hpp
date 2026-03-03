#include <stdint.h>

void flip_images_on_load(int boolean);

class image
{
private:
    uint32_t activeTextureID;
    uint32_t textureHandle;
public:
    image(const char* filePath);
    ~image();

    const uint32_t getTextureHandle();
    const uint32_t getActiveTextureID();
};