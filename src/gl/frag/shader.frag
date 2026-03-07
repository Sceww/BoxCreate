#version 330 core
out vec4 FragColor;

in vec3 aCol;
in vec2 texCoord;

uniform float time;

uniform sampler2D texture1;

void main() {
    // FragColor = vec4(texCoord, 0.0, 1.0);
    FragColor = texture(texture1, texCoord+vec2(time,time/2));
}