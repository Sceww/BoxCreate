#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 vCol; // 3 values; 3 floats; 3*4 = 12 bytes

out vec3 aCol;

// uniform vec4 globalTime;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    aCol = vCol;
}