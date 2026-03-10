#pragma once

#include <stdint.h>

#define MAX_NUMBER_OF_BOXES    128
#define VERTEX_ATTRIBUTE_COUNT 5

// box....
struct box {
    float vertices[VERTEX_ATTRIBUTE_COUNT * 4];
};

struct state_struct {
    uint32_t VAO=NULL, VBO=NULL, EBO=NULL;
     int32_t width=800, height=800;
    uint32_t indicesCount=0;
    uint32_t indices[(MAX_NUMBER_OF_BOXES*4) + ((MAX_NUMBER_OF_BOXES*4) / 2)];
    uint32_t numBoxes=0;
    box      boxes[MAX_NUMBER_OF_BOXES];
};

extern state_struct g_state;