#version 330 core
out vec4 FragColor;

in vec3 aCol;

uniform float globalTime;

void main() {
    // FragColor = vec4(0.0f, 0.5f, 0.5f, 1.0f);
    FragColor = vec4(aCol * globalTime, 1.0);
}