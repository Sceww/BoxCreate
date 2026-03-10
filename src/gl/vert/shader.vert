#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec2 uv;

out vec2 texCoord;

uniform float time;

void main() {
    // gl_Position = projection * view * modelTrans * vec4(aPos, 1.0);
    gl_Position = vec4(aPos, 1.0);
    texCoord = uv;
}