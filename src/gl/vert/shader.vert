#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 vCol;
layout (location=2) in vec2 uv;

out vec3 aCol;
out vec2 texCoord;

uniform float time;

vec2 calcVec2Rotation(float angle, vec2 vector);

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    aCol = vec3(uv, 1.0);
    texCoord = calcVec2Rotation(time, uv);
}

vec2 calcVec2Rotation(float angle, vec2 vector) {
    vector.x = (cos(angle)*vector.x) - (sin(angle)*vector.y);
    vector.y = (sin(angle)*vector.x) + (cos(angle)*vector.y);
    return vector;
}