#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 vCol;
layout (location=2) in vec2 uv;

out vec3 aCol;

// uniform vec4 globalTime;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    // aCol = (aPos+1) / 2.0;
    aCol = vec3(uv, 1.0);
}